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

#include "LinearTextGradientComponentInstance.h"
#include <bits/alltypes.h>
#include <glog/logging.h>
#include <react/renderer/components/text/ParagraphProps.h>
#include <react/renderer/core/ConcreteState.h>
#include "LinearTextGradientState.h"
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {
    LinearTextGradientComponentInstance::LinearTextGradientComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {
        m_stackNode.insertChild(m_textNode, 0);
    }

    void LinearTextGradientComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                              std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }
    void LinearTextGradientComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    LinearTextGradientTextNode &LinearTextGradientComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    void LinearTextGradientComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        CppComponentInstance::onPropsChanged(props);
        this->colors = props->colors;
        this->locations = props->locations;
        this->start = props->gradientStart;
        this->end = props->gradientEnd;
        float angle = this->computeAngle(this->start, this->end);
        this->getLocalRootArkUINode().setBlendMode(ARKUI_BLEND_MODE_SRC_OVER,
                                                   this->getLocalRootArkUINode().getArkUINodeHandle());
        this->getLocalRootArkUINode().setBlendMode(ARKUI_BLEND_MODE_DST_IN, this->m_textNode.getArkUINodeHandle());
        this->getLocalRootArkUINode().setLinearGradient(this->colors, props->locations, angle,
                                                        this->getLocalRootArkUINode().getArkUINodeHandle(),props->useGlobalCache);
    }
    void LinearTextGradientComponentInstance::onStateChanged(SharedConcreteState const &textState) {
        CppComponentInstance::onStateChanged(textState);
        DLOG(INFO) << "LinearTextGradientPackage::onStateChanged text: "
                  << textState->getData().attributedString.getString();
        for (auto fragment : textState->getData().attributedString.getFragments()) {
            auto fontSize = fragment.textAttributes.fontSize;
            if (fontSize) {
                this->m_textNode.setFontSize(fontSize);
                auto rnInstancePtr = this->m_deps->rnInstance.lock();
                if (rnInstancePtr != nullptr) {
                    auto turboModule = rnInstancePtr->getTurboModule("LinearTextGradientContext");
                    auto arkTsTurboModule = std::dynamic_pointer_cast<rnoh::ArkTSTurboModule>(turboModule);
                    std::vector<ArkJS::IntermediaryArg> args;
                    args.push_back(textState->getData().attributedString.getString());
                    args.push_back(fontSize);
                    auto result = arkTsTurboModule->callSync("measureTextSize", args);
                    double width = result["width"].asDouble();
                    double height = result["height"].asDouble();
                    this->getLocalRootArkUINode().setLayoutRect(m_layoutMetrics.frame.origin,{width,height},m_layoutMetrics.pointScaleFactor);
                }
            }
        }
        this->m_textNode.setTextContent(textState->getData().attributedString.getString());
    }


    facebook::react::Float LinearTextGradientComponentInstance::computeAngle(const facebook::react::Point &start,
                                                                             const facebook::react::Point &end) {
        float angle = 0;
        if (start.x == end.x) {
            if (start.y == end.y) {
                angle = 0;
            } else if (start.y < end.y) {
                angle = 180.0;
            } else {
                angle = 0;
            }
        } else if (start.y == end.y) {
            if (start.x == end.x) {
                angle = 90.0;
            } else if (start.x < end.x) {
                angle = 90.0;
            } else {
                angle = -90.0;
            }
        } else {
            float tan = (end.x - start.x) / (end.y - start.y);
            angle = 180.0 - atan(tan) * 180.0 / M_PI;
        }
        return angle;
    }
}