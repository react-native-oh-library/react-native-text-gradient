/**
 * MIT License
 *
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>
#include "Props.h"
#include <react/renderer/core/CoreFeatures.h>
#include <react/renderer/attributedstring/conversions.h>

namespace facebook {
    namespace react {

        RNLinearTextGradientProps::RNLinearTextGradientProps(const PropsParserContext &context,
                                                             const RNLinearTextGradientProps &sourceProps,
                                                             const RawProps &rawProps)
            : ViewProps(context, sourceProps, rawProps), BaseTextProps(context, sourceProps, rawProps),
              paragraphAttributes(CoreFeatures::enablePropIteratorSetter
                                      ? sourceProps.paragraphAttributes
                                      : convertRawProp(context, rawProps, sourceProps.paragraphAttributes, {})),

              useViewFrame(convertRawProp(context, rawProps, "useViewFrame", sourceProps.useViewFrame, {false})),
              useGlobalCache(convertRawProp(context, rawProps, "useGlobalCache", sourceProps.useGlobalCache, {false})),
              gradientStart(
                  convertRawProp(context, rawProps, "gradientStart", sourceProps.gradientStart, {.x = 0.5, .y = 0})),
              gradientEnd(
                  convertRawProp(context, rawProps, "gradientEnd", sourceProps.gradientEnd, {.x = 0.5, .y = 1})),
              colors(convertRawProp(context, rawProps, "colors", sourceProps.colors, {})),
              locations(convertRawProp(context, rawProps, "locations", sourceProps.locations, {})),
              fragments(convertRawProp(context, rawProps, "fragments", sourceProps.fragments, {})),
              onTextLayout(CoreFeatures::enablePropIteratorSetter
                               ? sourceProps.onTextLayout
                               : convertRawProp(context, rawProps, "onTextLayout", sourceProps.onTextLayout, {})) {
            textAttributes.opacity = std::numeric_limits<Float>::quiet_NaN();
            textAttributes.backgroundColor = {};
        };


        void RNLinearTextGradientProps::setProp(const PropsParserContext &context, RawPropsPropNameHash hash,
                                                const char *propName, RawValue const &value) {
            // All Props structs setProp methods must always, unconditionally,
            // call all super::setProp methods, since multiple structs may
            // reuse the same values.
            ViewProps::setProp(context, hash, propName, value);
            BaseTextProps::setProp(context, hash, propName, value);
        }

    } // namespace react
} // namespace facebook