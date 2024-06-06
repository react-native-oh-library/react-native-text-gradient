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

#ifndef HARMONY_LinearTextGradientComponentInstance_H
#define HARMONY_LinearTextGradientComponentInstance_H

#include "RNOH/CppComponentInstance.h"
#include "LinearTextGradientTextNode.h"
#include "Props.h"
#include "ShadowNodes.h"
#include "RNOH/arkui/SpanNode.h"
#include <folly/json.h>

namespace rnoh {
    class LinearTextGradientComponentInstance
        : public CppComponentInstance<facebook::react::RNLinearTextGradientShadowNode> {
    private:
        LinearTextGradientTextNode m_stackNode;
        std::vector<facebook::react::SharedColor> colors;
        facebook::react::Float angle;
        std::vector<facebook::react::Float> locations;
        facebook::react::Point start;
        facebook::react::Point end;
        std::vector<float> stops;
        RNTextNode m_textNode;

    public:
        LinearTextGradientComponentInstance(Context context);
        void onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) override;

        void onChildRemoved(ComponentInstance::Shared const &childComponentInstance) override;

        LinearTextGradientTextNode &getLocalRootArkUINode() override;

        void onPropsChanged(SharedConcreteProps const &props) override;

        void onStateChanged(SharedConcreteState const &textState) override;

        facebook::react::Float computeAngle(const facebook::react::Point &start, const facebook::react::Point &end);

    };
} // namespace rnoh

#endif // HARMONY_LinearTextGradientComponentInstance_H
