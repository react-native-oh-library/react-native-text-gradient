#pragma once

#include "RNOH/arkui/ArkUINode.h"
#include "react/renderer/attributedstring/primitives.h"

namespace rnoh {

class RNTextNode : public ArkUINode {
 private:
  enum {
    FLAG_PADDING = 0,
    FLAG_MINFONTSIZE,
    FLAG_MAXFONTSIZE,
    FLAG_COPYOPTION,
    FLAG_ENABLE,
    FLAG_MAX
  };
  bool m_initFlag[FLAG_MAX] = {0};

  float m_minFontSize = 0.0;
  float m_maxFontSize = 0.0;
  int32_t m_testCopyOption = 0;
  bool m_enableFlag = false;
  float m_top = 0.0;
  float m_right = 0.0;
  float m_bottom = 0.0;
  float m_left = 0.0;

 public:
  RNTextNode();

  void insertChild(ArkUINode& child, std::size_t index);
  void removeChild(ArkUINode& child);

  RNTextNode& setTextContent(const std::string& text);
  RNTextNode& setFontColor(uint32_t fontColor);
  RNTextNode& resetFontColor();
  RNTextNode& setFontSize(float fontSize);
  RNTextNode& setFontStyle(int32_t fontStyle);
  RNTextNode& setFontWeight(int32_t fontWeight);
  RNTextNode& setTextLineHeight(float textLineHeight);
  RNTextNode& setTextDecoration(
      int32_t decorationStyle,
      uint32_t decorationColor = 0xFFFF0000);
  RNTextNode& setTextCase(int32_t textCase);
  RNTextNode& setTextLetterSpacing(float textLetterSpacing);
  RNTextNode& setTextMaxLines(int32_t textMaxLines);
  RNTextNode& resetTextMaxLines();
  RNTextNode& setTextAlign(int32_t align);
  RNTextNode& setTextEllipsisMode(int32_t ellipsisMode);
  RNTextNode& setTextOverflow(int32_t textOverflow);
  RNTextNode& setFontFamily(const std::string& fontFamily);
  RNTextNode& setTextCopyOption(int32_t testCopyOption);
  RNTextNode& setTextBaselineOffset(float textBaselineOffset);
  RNTextNode& setTextShadow(
      float textShadowRadius,
      int32_t textShadowType,
      uint32_t textShadowColor,
      float textShadowOffsetX,
      float textShadowOffsetY);
  RNTextNode& setMinFontSize(float minFontSize);
  RNTextNode& setMaxFontSize(float maxFontSize);
  RNTextNode& setTextFont(
      float fontSize,
      int32_t fontWeight = ARKUI_FONT_WEIGHT_NORMAL,
      int32_t fontStyle = ARKUI_FONT_STYLE_NORMAL,
      const std::string& fontFamily = std::string());
  RNTextNode& setTextHeightAdaptivePolicy(int32_t policyType);
  RNTextNode& setTextIndent(float textIndent);
  RNTextNode& setTextEnable(bool enableFlag);
  RNTextNode& setPadding(float top, float right, float bottom, float left);
};

} // namespace rnoh