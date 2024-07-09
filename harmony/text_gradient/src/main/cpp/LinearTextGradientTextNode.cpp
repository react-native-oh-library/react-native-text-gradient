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
#include "LinearTextGradientTextNode.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include <memory>
#include "glog/logging.h"

static std::map<ArkUI_NodeHandle,std::vector<facebook::react::SharedColor>> m_UseGlobCache;

namespace rnoh {
    LinearTextGradientTextNode::LinearTextGradientTextNode()
        : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_STACK)) {}

    void LinearTextGradientTextNode::insertChild(ArkUINode &child, std::size_t index) {
        maybeThrow(NativeNodeApi::getInstance()->insertChildAt(m_nodeHandle, child.getArkUINodeHandle(), index));
    }

    void LinearTextGradientTextNode::removeChild(ArkUINode &child) {
        maybeThrow(NativeNodeApi::getInstance()->removeChild(m_nodeHandle, child.getArkUINodeHandle()));
        setBlendMode(ARKUI_BLEND_MODE_NONE, getArkUINodeHandle());
        setBlendMode(ARKUI_BLEND_MODE_NONE, child.getArkUINodeHandle());
    }


    void LinearTextGradientTextNode::setBlendMode(int32_t blendMode, ArkUI_NodeHandle nodeHandle) {
        ArkUI_NumberValue value[] = {{.i32 = blendMode}, {.i32 = BLEND_APPLY_TYPE_OFFSCREEN}};
        ArkUI_AttributeItem item = {.value = value, .size = sizeof(value) / sizeof(ArkUI_NumberValue)};
        maybeThrow(NativeNodeApi::getInstance()->setAttribute(nodeHandle, NODE_BLEND_MODE, &item));
    }

    void LinearTextGradientTextNode::setLinearGradient(std::vector<facebook::react::SharedColor> &colors,
                                                       std::vector<facebook::react::Float> locations, float &angle,
                                                       ArkUI_NodeHandle nodeHandle,bool useGlobalCache) {
        if(useGlobalCache && m_UseGlobCache.find(nodeHandle)!=m_UseGlobCache.end() && colors.size()<=0){
           colors = m_UseGlobCache.find(nodeHandle)->second;
        }
        std::vector<uint32_t> colorsInput;
        std::vector<float> stopsInput;
        for (auto color : colors) {
            uint32_t colorValue = *color;
            colorsInput.push_back(colorValue);
        }
        for (facebook::react::Float location : locations) {
            stopsInput.push_back(location);
        }

        ArkUI_ColorStop colorStop = {colorsInput.data(), stopsInput.data(), static_cast<int>(colorsInput.size())};
        ArkUI_NumberValue linearGradientValue[] = {
            {.f32 = angle}, {.i32 = ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM}, {.i32 = 0}};
        ArkUI_AttributeItem linearGradientItem = {linearGradientValue,
                                                  sizeof(linearGradientValue) / sizeof(ArkUI_NumberValue),
                                                  .object = reinterpret_cast<void *>(&colorStop)};
        maybeThrow(NativeNodeApi::getInstance()->setAttribute(nodeHandle, NODE_LINEAR_GRADIENT, &linearGradientItem));
        m_UseGlobCache[nodeHandle] = colors;
    }


} // namespace rnoh