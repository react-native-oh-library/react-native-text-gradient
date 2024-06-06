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

#include "LinearTextGradientEventEmitter.h"

namespace facebook::react {

static jsi::Value linesMeasurementsPayload(
    jsi::Runtime &runtime,
    LinesMeasurements const &linesMeasurements) {
  auto payload = jsi::Object(runtime);
  auto lines = jsi::Array(runtime, linesMeasurements.size());

  for (size_t i = 0; i < linesMeasurements.size(); ++i) {
    auto const &lineMeasurement = linesMeasurements[i];
    auto jsiLine = jsi::Object(runtime);
    jsiLine.setProperty(runtime, "text", lineMeasurement.text);
    jsiLine.setProperty(runtime, "x", lineMeasurement.frame.origin.x);
    jsiLine.setProperty(runtime, "y", lineMeasurement.frame.origin.y);
    jsiLine.setProperty(runtime, "width", lineMeasurement.frame.size.width);
    jsiLine.setProperty(runtime, "height", lineMeasurement.frame.size.height);
    jsiLine.setProperty(runtime, "descender", lineMeasurement.descender);
    jsiLine.setProperty(runtime, "capHeight", lineMeasurement.capHeight);
    jsiLine.setProperty(runtime, "ascender", lineMeasurement.ascender);
    jsiLine.setProperty(runtime, "xHeight", lineMeasurement.xHeight);
    lines.setValueAtIndex(runtime, i, jsiLine);
  }

  payload.setProperty(runtime, "lines", lines);

  return payload;
}

void LinearTextGradientEventEmitter::onTextLayout(
    LinesMeasurements const &linesMeasurements) const {
  {
    std::lock_guard<std::mutex> guard(linesMeasurementsMutex_);
    if (linesMeasurementsMetrics_ == linesMeasurements) {
      return;
    }
    linesMeasurementsMetrics_ = linesMeasurements;
  }

  dispatchEvent("textLayout", [linesMeasurements](jsi::Runtime &runtime) {
    return linesMeasurementsPayload(runtime, linesMeasurements);
  });
}

} // namespace facebook::react