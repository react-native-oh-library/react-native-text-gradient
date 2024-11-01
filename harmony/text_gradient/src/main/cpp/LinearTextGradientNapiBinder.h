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

#ifndef HARMONY_LINEAR_TEXT_GRADIENT_SRC_MAIN_CPP_LINEARTEXTGRADIENTNAPIBINDER_H
#define HARMONY_LINEAR_TEXTGRADIENT_SRC_MAIN_CPP_LINEARTEXTGRADIENTNAPIBINDER_H
#include "RNOHCorePackage/ComponentBinders/ViewComponentNapiBinder.h"
#include "Props.h"
#include "react/renderer/components/text/ParagraphState.h"
#include "react/renderer/core/ConcreteState.h"
#include <react/renderer/components/text/ParagraphProps.h>
#include <react/renderer/components/text/ParagraphState.h>
#include <react/renderer/components/view/YogaStylableProps.h>
#include <react/renderer/components/view/conversions.h>
#include <react/renderer/core/ConcreteState.h>
#include <react/renderer/core/LayoutPrimitives.h>
#include "RNOH/ShadowViewRegistry.h"
#include "RNOHCorePackage/ComponentBinders/ViewComponentNapiBinder.h"
namespace rnoh {
    class LinearTextGradientNapiBinder : public ViewComponentNapiBinder {
    public:
        napi_value createProps(napi_env env, facebook::react::ShadowView const shadowView) override {
            napi_value napiViewProps = ViewComponentNapiBinder::createProps(env, shadowView);
            auto propsObjBuilder = ArkJS(env).getObjectBuilder(napiViewProps);
            auto fragmentsPayload = std::vector<napi_value>();
            if (auto state =
                    std::dynamic_pointer_cast<const facebook::react::ConcreteState<facebook::react::ParagraphState>>(
                        shadowView.state)) {
                auto data = state->getData();
                auto fragments = data.attributedString.getFragments();
                auto fragmentObjBuilder = ArkJS(env).createObjectBuilder();
                for (auto fragment : fragments) {
                    fragmentObjBuilder.addProperty("text", fragment.string);
                }
                fragmentsPayload.push_back(fragmentObjBuilder.build());
            }
        if (auto props =
                    std::dynamic_pointer_cast<const facebook::react::RNLinearTextGradientProps>(shadowView.props)) {
                auto colors = std::vector<napi_value>();
                auto colorsRaw = props->colors;
                for (auto color : colorsRaw) {
                    auto colorObjBuilder = ArkJS(env).createObjectBuilder();
                    colorObjBuilder.addProperty("color", color);
                    colors.push_back(colorObjBuilder.build());
                }
                auto colorsArray = ArkJS(env).createArray(colors);

                auto locations = std::vector<napi_value>();
                auto locationsRaw = props->locations;
                for (auto location : locationsRaw) {
                    auto locationObjBuilder = ArkJS(env).createObjectBuilder();
                    locationObjBuilder.addProperty("location", location);
                    locations.push_back(locationObjBuilder.build());
                }
                auto locationsArray = ArkJS(env).createArray(locations);

                auto startPointObj = ArkJS(env)
                                         .createObjectBuilder()
                                         .addProperty("x", props->gradientStart.x)
                                         .addProperty("y", props->gradientStart.y)
                                         .build();
                auto endPointObj = ArkJS(env)
                                       .createObjectBuilder()
                                       .addProperty("x", props->gradientEnd.x)
                                       .addProperty("y", props->gradientEnd.y)
                                       .build();

                auto fragmentsArray = ArkJS(env).createArray(fragmentsPayload);
                propsObjBuilder.addProperty("fragments", fragmentsArray)
                    .addProperty("colors", colorsArray)
                    .addProperty("locations", locationsArray)
                    .addProperty("start", startPointObj)
                    .addProperty("end", endPointObj);
                return propsObjBuilder.build();
            }
            return napiViewProps;
        };
    };

} // namespace rnoh
#endif
