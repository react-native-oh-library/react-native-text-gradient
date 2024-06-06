//
// Created on 2024/6/5.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_LINEARTEXTGRADIENTSTATE_H
#define HARMONY_LINEARTEXTGRADIENTSTATE_H
#include <react/debug/react_native_assert.h>
#include <react/renderer/attributedstring/AttributedString.h>
#include <react/renderer/attributedstring/ParagraphAttributes.h>
#include "LinearTextGradientLayoutManager.h"

#ifdef ANDROID
#include <folly/dynamic.h>
#include <react/renderer/mapbuffer/MapBuffer.h>
#endif

namespace facebook::react {

#ifdef ANDROID
// constants for Text State serialization
constexpr static MapBuffer::Key TX_STATE_KEY_ATTRIBUTED_STRING = 0;
constexpr static MapBuffer::Key TX_STATE_KEY_PARAGRAPH_ATTRIBUTES = 1;
// Used for TextInput only
constexpr static MapBuffer::Key TX_STATE_KEY_HASH = 2;
constexpr static MapBuffer::Key TX_STATE_KEY_MOST_RECENT_EVENT_COUNT = 3;
#endif

/*
 * State for <Paragraph> component.
 * Represents what to render and how to render.
 */
struct LinearTextGradientState {
  /*
   * All content of <Paragraph> component represented as an `AttributedString`.
   */
  AttributedString attributedString;

  /*
   * Represents all visual attributes of a paragraph of text represented as
   * a ParagraphAttributes.
   */
  ParagraphAttributes paragraphAttributes;

  /*
   * `ParagraphLayoutManager` provides a connection to platform-specific
   * text rendering infrastructure which is capable to render the
   * `AttributedString`.
   * This is not on every platform. This is not used on Android, but is
   * used on the iOS mounting layer.
   */
  LinearTextGradientLayoutManager linearTextGradientLayoutManager;
};

} // namespace facebook::react

#endif //HARMONY_LINEARTEXTGRADIENTSTATE_H
