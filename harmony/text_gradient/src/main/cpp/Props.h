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

#ifndef HARMONY_LINEAR_TEXT_GRADIENT_SRC_MAIN_CPP_PROPS_H
#define HARMONY_LINEAR_TEXT_GRADIENT_SRC_MAIN_CPP_PROPS_H

#include <react/renderer/components/text/BaseTextProps.h>
#include "react/renderer/attributedstring/ParagraphAttributes.h"
#include "react/renderer/components/view/ViewProps.h"
#include <jsi/jsi.h>
#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>
#include <vector>

namespace facebook {
namespace react {

class JSI_EXPORT RNLinearTextGradientProps final : public ViewProps, public BaseTextProps {
 public:
  RNLinearTextGradientProps() = default;
  RNLinearTextGradientProps(const PropsParserContext& context, const RNLinearTextGradientProps &sourceProps, const RawProps &rawProps);

  void setProp(const PropsParserContext &context, RawPropsPropNameHash hash, const char *propName,
               RawValue const &value);

#pragma mark - Props

  Point gradientStart{};
  Point gradientEnd{};
  std::vector<SharedColor> colors{};
  std::vector<Float> locations{};
  std::vector<std::string> fragments{};
  bool useViewFrame{false};
  bool useGlobalCache{false};
  ParagraphAttributes paragraphAttributes{};
  bool onTextLayout{};
};

} // namespace react
} // namespace facebook
#endif