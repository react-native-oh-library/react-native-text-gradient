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
#include "RNOH/Package.h"
#include "ComponentDescriptors.h"
#include "LinearTextGradientJSIBinder.h"
#include "LinearTextGradientNapiBinder.h"
#include "LinearTextGradientComponentInstance.h"
#include "LinearTextGradientTurboModule.h"

using namespace rnoh;
using namespace facebook;
namespace rnoh{

    class LinearTextGradientComponentInstanceFactoryDelegate : public ComponentInstanceFactoryDelegate {
    public:
        using ComponentInstanceFactoryDelegate::ComponentInstanceFactoryDelegate;

        ComponentInstance::Shared create(ComponentInstance::Context ctx) override {
            if (ctx.componentName == "RNLinearTextGradient") {
                return std::make_shared<LinearTextGradientComponentInstance>(std::move(ctx));
            }
            return nullptr;
        }
    };


    class LinearTextGradientContextFactoryDelegate : public TurboModuleFactoryDelegate {
    public:
        SharedTurboModule createTurboModule(Context ctx, const std::string &name) const override {
            if (name == "LinearTextGradientContext") {
                return std::make_shared<LinearTextGradientTurboModule>(ctx, name);
            }
            return nullptr;
        };
    };

  class LinearTextGradientPackage : public Package{
    public:
      LinearTextGradientPackage(Package::Context ctx) : Package(ctx){}

      ComponentInstanceFactoryDelegate::Shared createComponentInstanceFactoryDelegate() override {
            return std::make_shared<LinearTextGradientComponentInstanceFactoryDelegate>();
      }

      std::unique_ptr<TurboModuleFactoryDelegate> createTurboModuleFactoryDelegate() override {
            return std::make_unique<LinearTextGradientContextFactoryDelegate>();
      }

      std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() override
      {
        return {
          facebook::react::concreteComponentDescriptorProvider<facebook::react::RNLinearTextGradientComponentDescriptor>(),
        };
      }

      ComponentJSIBinderByString createComponentJSIBinderByName() override
      {
        return {{"RNLinearTextGradient",std::make_shared<LinearTextGradientJSIBinder>()}};
      };

      ComponentNapiBinderByString createComponentNapiBinderByName() override
      {
        return {{"RNLinearTextGradient",std::make_shared<LinearTextGradientNapiBinder>()}};
      };
    
  };
} // namespace rnoh