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

#ifndef HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTJSIBINDER_H
#define HARMONY_LINEAR_GRADIENT_SRC_MAIN_CPP_LINEARGRADIENTJSIBINDER_H
#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
    class LinearTextGradientJSIBinder : public ViewComponentJSIBinder {
        facebook::jsi::Object createNativeProps(facebook::jsi::Runtime &rt) override {
            auto object = ViewComponentJSIBinder::createNativeProps(rt);
            object.setProperty(rt, "colors", "array");
            object.setProperty(rt, "locations", "array");
            object.setProperty(rt, "gradientStart", "object");
            object.setProperty(rt, "gradientEnd", "object");
            object.setProperty(rt, "fragments", "array");
            object.setProperty(rt, "useViewFrame", "boolean");
            object.setProperty(rt, "useGlobalCache", "boolean");
            return object;
        }
    };
} // namespace  rnoh
#endif