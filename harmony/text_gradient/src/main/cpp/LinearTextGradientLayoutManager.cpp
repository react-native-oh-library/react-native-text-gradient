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
#include "LinearTextGradientLayoutManager.h"
#include <folly/Hash.h>
#include <react/renderer/core/CoreFeatures.h>

namespace facebook::react {

TextMeasurement LinearTextGradientLayoutManager::measure(
    AttributedString const &attributedString,
    ParagraphAttributes const &paragraphAttributes,
    LayoutConstraints layoutConstraints) const {
  bool cacheLastTextMeasurement = CoreFeatures::cacheLastTextMeasurement;
  if (cacheLastTextMeasurement &&
      (layoutConstraints.maximumSize.width == availableWidth_ ||
       layoutConstraints.maximumSize.width ==
           cachedTextMeasurement_.size.width)) {
    return cachedTextMeasurement_;
  }
  if (CoreFeatures::cacheNSTextStorage) {
    size_t newHash = folly::hash::hash_combine(
        0,
        textAttributedStringHashLayoutWise(attributedString),
        paragraphAttributes);

    if (!hostTextStorage_ || newHash != hash_) {
      hostTextStorage_ = textLayoutManager_->getHostTextStorage(
          attributedString, paragraphAttributes, layoutConstraints);
      hash_ = newHash;
    }
  }

  if (cacheLastTextMeasurement) {
    cachedTextMeasurement_ = textLayoutManager_->measure(
        AttributedStringBox(attributedString),
        paragraphAttributes,
        layoutConstraints,
        hostTextStorage_);

    availableWidth_ = layoutConstraints.maximumSize.width;
    return cachedTextMeasurement_;
  } else {
    return textLayoutManager_->measure(
        AttributedStringBox(attributedString),
        paragraphAttributes,
        layoutConstraints,
        hostTextStorage_);
  }
}

LinesMeasurements LinearTextGradientLayoutManager::measureLines(
    AttributedString const &attributedString,
    ParagraphAttributes const &paragraphAttributes,
    Size size) const {
          LOG(INFO) << "LinearTextGradientLayoutManager measureLines w:" << size.width
              << " h:" << size.height;
  return textLayoutManager_->measureLines(
      attributedString, paragraphAttributes, size);
}

void LinearTextGradientLayoutManager::setTextLayoutManager(
    std::shared_ptr<TextLayoutManager const> textLayoutManager) const {
  textLayoutManager_ = std::move(textLayoutManager);
}

std::shared_ptr<TextLayoutManager const>
LinearTextGradientLayoutManager::getTextLayoutManager() const {
  return textLayoutManager_;
}

std::shared_ptr<void> LinearTextGradientLayoutManager::getHostTextStorage() const {
  return hostTextStorage_;
}
} // namespace facebook::react