/**
 * MIT License
 *
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "ShadowNodes.h"
#include "LinearTextGradientState.h"
#include "react/renderer/core/TraitCast.h"
#include "react/renderer/graphics/rounding.h"
#include "react/renderer/core/TraitCast.h"

namespace facebook {
namespace react {

extern const char RNLinearTextGradientComponentName[] = "RNLinearTextGradient";

using Content = RNLinearTextGradientShadowNode::Content;


Content const &RNLinearTextGradientShadowNode::getContent(
    LayoutContext const &layoutContext) const {
  if (content_.has_value()) {
    return content_.value();
  }

  ensureUnsealed();

  auto textAttributes = TextAttributes::defaultTextAttributes();
  textAttributes.fontSizeMultiplier = layoutContext.fontSizeMultiplier;
  textAttributes.apply(getConcreteProps().textAttributes);
  textAttributes.layoutDirection =
      YGNodeLayoutGetDirection(&yogaNode_) == YGDirectionRTL
      ? LayoutDirection::RightToLeft
      : LayoutDirection::LeftToRight;
  auto attributedString = AttributedString{};
  auto attachments = Attachments{};
  buildAttributedString(textAttributes, *this, attributedString, attachments);

  content_ = Content{
      attributedString, getConcreteProps().paragraphAttributes, attachments};

  return content_.value();
}

void RNLinearTextGradientShadowNode::setTextLayoutManager(
    std::shared_ptr<TextLayoutManager const> textLayoutManager) {
  ensureUnsealed();
  getStateData().linearTextGradientLayoutManager.setTextLayoutManager(
      std::move(textLayoutManager));
}

void RNLinearTextGradientShadowNode::updateStateIfNeeded(Content const &content) {
  ensureUnsealed();
  auto &state = getStateData();
    state.linearTextGradientLayoutManager;
  react_native_assert(state.linearTextGradientLayoutManager.getTextLayoutManager());

  if (state.attributedString == content.attributedString) {
    return;
  }

  setStateData(LinearTextGradientState{
      content.attributedString,
      content.paragraphAttributes,
      state.linearTextGradientLayoutManager});
}

#pragma mark - LayoutableShadowNode

Content
RNLinearTextGradientShadowNode::getContentWithMeasuredAttachments(LayoutContext const &layoutContext,
                                                                  LayoutConstraints const &layoutConstraints) const {
  auto content = getContent(layoutContext);

  if (content.attachments.empty()) {
    // Base case: No attachments, nothing to do.
    return content;
  }

  auto localLayoutConstraints = layoutConstraints;
  // Having enforced minimum size for text fragments doesn't make much sense.
  localLayoutConstraints.minimumSize = Size{0, 0};

  auto &fragments = content.attributedString.getFragments();

  for (auto const &attachment : content.attachments) {
    auto laytableShadowNode = traitCast<LayoutableShadowNode const *>(attachment.shadowNode);

    if (laytableShadowNode == nullptr) {
        continue;
    }

    auto size = laytableShadowNode->measure(layoutContext, localLayoutConstraints);

    // Rounding to *next* value on the pixel grid.
    size.width += 0.01f;
    size.height += 0.01f;
    size = roundToPixel<&ceil>(size, layoutContext.pointScaleFactor);

    auto fragmentLayoutMetrics = LayoutMetrics{};
    fragmentLayoutMetrics.pointScaleFactor = layoutContext.pointScaleFactor;
    fragmentLayoutMetrics.frame.size = size;
    fragments[attachment.fragmentIndex].parentShadowView.layoutMetrics = fragmentLayoutMetrics;
  }

  return content;
}
    
    
Size RNLinearTextGradientShadowNode::measureContent(
    LayoutContext const &layoutContext,
    LayoutConstraints const &layoutConstraints) const {
  auto content =
      getContentWithMeasuredAttachments(layoutContext, layoutConstraints);
  auto attributedString = content.attributedString;
  if (attributedString.isEmpty()) {
    // Note: `zero-width space` is insufficient in some cases (e.g. when we need
    // to measure the "height" of the font).
    // TODO T67606511: We will redefine the measurement of empty strings as part
    // of T67606511
    auto string = BaseTextShadowNode::getEmptyPlaceholder();
    auto textAttributes = TextAttributes::defaultTextAttributes();
    textAttributes.fontSizeMultiplier = layoutContext.fontSizeMultiplier;
    textAttributes.apply(getConcreteProps().textAttributes);
    attributedString.appendFragment({string, textAttributes, {}});
  }
  Size ddd= getStateData()
      .linearTextGradientLayoutManager
      .measure(attributedString, content.paragraphAttributes, layoutConstraints)
      .size;

  return getStateData()
      .linearTextGradientLayoutManager
      .measure(attributedString, content.paragraphAttributes, layoutConstraints)
      .size;
}

void RNLinearTextGradientShadowNode::layout(LayoutContext layoutContext) {
  ensureUnsealed();

  auto layoutMetrics = getLayoutMetrics();
  auto availableSize = layoutMetrics.getContentFrame().size;

  auto layoutConstraints = LayoutConstraints{
      availableSize, availableSize, layoutMetrics.layoutDirection};

   auto content = getContentWithMeasuredAttachments(layoutContext, layoutConstraints);

   updateStateIfNeeded(content);

   auto measurement = getStateData().linearTextGradientLayoutManager.measure(
       content.attributedString, content.paragraphAttributes, layoutConstraints);
 

   if (getConcreteProps().onTextLayout) {
    auto linesMeasurements = getStateData().linearTextGradientLayoutManager.measureLines(
        content.attributedString,
        content.paragraphAttributes,
        measurement.size);
    getConcreteEventEmitter().onTextLayout(linesMeasurements);
  }

  if (content.attachments.empty()) {
    // No attachments to layout.
    return;
  }
    
 //  Iterating on attachments, we clone shadow nodes and moving
  //  `paragraphShadowNode` that represents clones of `this` object.
  auto paragraphShadowNode = static_cast<RNLinearTextGradientShadowNode *>(this);
  // `paragraphOwningShadowNode` is owning pointer to`paragraphShadowNode`
  // (besides the initial case when `paragraphShadowNode == this`), we need this
  // only to keep it in memory for a while.
  auto paragraphOwningShadowNode = ShadowNode::Unshared{};

  react_native_assert(
      content.attachments.size() == measurement.attachments.size());

  for (size_t i = 0; i < content.attachments.size(); i++) {
    auto &attachment = content.attachments.at(i);

    if (traitCast<LayoutableShadowNode const *>(attachment.shadowNode) ==
        nullptr) {
      // Not a layoutable `ShadowNode`, no need to lay it out.
      continue;
    }

    auto clonedShadowNode = ShadowNode::Unshared{};

    paragraphOwningShadowNode = paragraphShadowNode->cloneTree(
        attachment.shadowNode->getFamily(),
        [&](ShadowNode const &oldShadowNode) {
          clonedShadowNode = oldShadowNode.clone({});
          return clonedShadowNode;
        });
    paragraphShadowNode =
        static_cast<RNLinearTextGradientShadowNode *>(paragraphOwningShadowNode.get());

    auto &layoutableShadowNode =
        traitCast<LayoutableShadowNode &>(*clonedShadowNode);

    auto attachmentFrame = measurement.attachments[i].frame;
    auto attachmentSize = roundToPixel<&ceil>(
        attachmentFrame.size, layoutMetrics.pointScaleFactor);
    auto attachmentOrigin = roundToPixel<&round>(
        attachmentFrame.origin, layoutMetrics.pointScaleFactor);
    auto attachmentLayoutContext = layoutContext;
    auto attachmentLayoutConstrains = LayoutConstraints{
        attachmentSize, attachmentSize, layoutConstraints.layoutDirection};

    // Laying out the `ShadowNode` and the subtree starting from it.
    layoutableShadowNode.layoutTree(
        attachmentLayoutContext, attachmentLayoutConstrains);

    // Altering the origin of the `ShadowNode` (which is defined by text layout,
    // not by internal styles and state).
    auto attachmentLayoutMetrics = layoutableShadowNode.getLayoutMetrics();
    attachmentLayoutMetrics.frame.origin = attachmentOrigin;
    layoutableShadowNode.setLayoutMetrics(attachmentLayoutMetrics);
  }
    
 // If we ended up cloning something, we need to update the list of children to
  // reflect the changes that we made.
  if (paragraphShadowNode != this) {
    this->children_ =
        static_cast<RNLinearTextGradientShadowNode const *>(paragraphShadowNode)
            ->children_;
  }
}
} // namespace react
} // namespace facebook   
