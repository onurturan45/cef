// Copyright (c) 2010 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "../include/cef.h"
#include "base/utf_string_conversions.h"
#include "webkit/glue/webpreferences.h"

void BrowserToWebSettings(const CefBrowserSettings& cef, WebPreferences& web)
{
  if (cef.standard_font_family)
    web.standard_font_family = cef.standard_font_family;
  else
    web.standard_font_family = L"Times";
  
  if (cef.fixed_font_family)
    web.fixed_font_family = cef.fixed_font_family;
  else
    web.fixed_font_family = L"Courier";
  
  if (cef.serif_font_family)
    web.serif_font_family = cef.serif_font_family;
  else
    web.serif_font_family = L"Times";

  if (cef.sans_serif_font_family)
    web.sans_serif_font_family = cef.sans_serif_font_family;
  else
    web.sans_serif_font_family = L"Helvetica";

  // These two fonts below are picked from the intersection of
  // Win XP font list and Vista font list :
  //   http://www.microsoft.com/typography/fonts/winxp.htm 
  //   http://blogs.msdn.com/michkap/archive/2006/04/04/567881.aspx
  // Some of them are installed only with CJK and complex script
  // support enabled on Windows XP and are out of consideration here. 
  // (although we enabled both on our buildbots.)
  // They (especially Impact for fantasy) are not typical cursive
  // and fantasy fonts, but it should not matter for layout tests
  // as long as they're available.

  if (cef.cursive_font_family) {
    web.cursive_font_family = cef.cursive_font_family;
  } else {
#if defined(OS_MACOSX)
    web.cursive_font_family = L"Apple Chancery";
#else
    web.cursive_font_family = L"Comic Sans MS";
#endif
  }

  if (cef.fantasy_font_family) {
    web.fantasy_font_family = cef.fantasy_font_family;
  } else {
#if defined(OS_MACOSX)
    web.fantasy_font_family = L"Papyrus";
#else
    web.fantasy_font_family = L"Impact";
#endif
  }

  if (cef.default_font_size > 0)
    web.default_font_size = cef.default_font_size;
  else
    web.default_font_size = 16;

  if (cef.default_fixed_font_size > 0)
    web.default_fixed_font_size = cef.default_fixed_font_size;
  else
    web.default_fixed_font_size = 13;

  if (cef.minimum_font_size > 0)
    web.minimum_font_size = cef.minimum_font_size;
  else
    web.minimum_font_size = 1;

  if (cef.minimum_logical_font_size > 0)
    web.minimum_logical_font_size = cef.minimum_logical_font_size;
  else
    web.minimum_logical_font_size = 9;
  
  if (cef.default_encoding)
    web.default_encoding = WideToUTF8(cef.default_encoding);
  else
    web.default_encoding = "ISO-8859-1";

  web.javascript_enabled = !cef.javascript_disabled;
  web.web_security_enabled = !cef.web_security_disabled;
  web.javascript_can_open_windows_automatically =
      !cef.javascript_open_windows_disallowed;
  web.loads_images_automatically = !cef.image_load_disabled;
  web.plugins_enabled = !cef.plugins_disabled;
  web.dom_paste_enabled = !cef.dom_paste_disabled;
  web.developer_extras_enabled = false;
  web.inspector_settings.clear();
  web.site_specific_quirks_enabled = !cef.site_specific_quirks_disabled;
  web.shrinks_standalone_images_to_fit = cef.shrink_standalone_images_to_fit;
  web.uses_universal_detector = cef.encoding_detector_enabled;
  web.text_areas_are_resizable = !cef.text_area_resize_disabled;
  web.java_enabled = !cef.java_disabled;
  web.allow_scripts_to_close_windows = !cef.javascript_close_windows_disallowed;
  web.uses_page_cache = !cef.page_cache_disabled;
  web.remote_fonts_enabled = !cef.remote_fonts_disabled;
  web.javascript_can_access_clipboard =
      !cef.javascript_access_clipboard_disallowed;
  web.xss_auditor_enabled = cef.xss_auditor_enabled;
  web.local_storage_enabled = !cef.local_storage_disabled;
  web.databases_enabled = !cef.databases_disabled;
  web.application_cache_enabled = !cef.application_cache_disabled;
  web.tabs_to_links = !cef.tab_to_links_disabled;
  web.caret_browsing_enabled = cef.caret_browsing_enabled;
  web.hyperlink_auditing_enabled = !cef.hyperlink_auditing_disabled;

  web.user_style_sheet_enabled = cef.user_style_sheet_enabled;

  if (cef.user_style_sheet_location) {
    web.user_style_sheet_location =
        GURL(WideToUTF8(cef.user_style_sheet_location));
  }

  web.author_and_user_styles_enabled = !cef.author_and_user_styles_disabled;
  web.allow_universal_access_from_file_urls =
      cef.universal_access_from_file_urls_allowed;
  web.allow_file_access_from_file_urls = cef.file_access_from_file_urls_allowed;
  web.experimental_webgl_enabled = cef.experimental_webgl_enabled;
  web.show_composited_layer_borders = false;
  web.accelerated_compositing_enabled = !cef.accelerated_compositing_disabled;
  web.accelerated_2d_canvas_enabled = !cef.accelerated_2d_canvas_disabled;
  web.memory_info_enabled = false;
}

void WebToBrowserSettings(const WebPreferences& web, CefBrowserSettings& cef)
{
  cef.Reset();

  if (!web.standard_font_family.empty()) {
    cef.standard_font_family =
        cef_string_alloc(web.standard_font_family.c_str());
  }

  if (!web.fixed_font_family.empty()) {
    cef.fixed_font_family =
        cef_string_alloc(web.fixed_font_family.c_str());
  }

  if (!web.serif_font_family.empty()) {
    cef.serif_font_family =
        cef_string_alloc(web.serif_font_family.c_str());
  }

  if (!web.cursive_font_family.empty()) {
    cef.cursive_font_family =
        cef_string_alloc(web.cursive_font_family.c_str());
  }

  if (!web.fantasy_font_family.empty()) {
    cef.fantasy_font_family =
        cef_string_alloc(web.fantasy_font_family.c_str());
  }

  cef.default_font_size = web.default_font_size;
  cef.default_fixed_font_size = web.default_fixed_font_size;
  cef.minimum_font_size = web.minimum_font_size;
  cef.minimum_logical_font_size = web.minimum_logical_font_size;
  cef.remote_fonts_disabled = !web.remote_fonts_enabled;
  
  if (!web.default_encoding.empty()) {
    std::wstring wstr;
    UTF8ToWide(web.default_encoding.c_str(), web.default_encoding.length(),
        &wstr);
    cef.default_encoding = cef_string_alloc(wstr.c_str());
  }

  cef.encoding_detector_enabled = web.uses_universal_detector;
  cef.javascript_disabled = !web.java_enabled;
  cef.javascript_open_windows_disallowed =
      !web.javascript_can_open_windows_automatically;
  cef.javascript_close_windows_disallowed =
      !web.allow_scripts_to_close_windows;
  cef.javascript_access_clipboard_disallowed =
      !web.javascript_can_access_clipboard;
  cef.dom_paste_disabled = !web.dom_paste_enabled;
  cef.caret_browsing_enabled = web.caret_browsing_enabled;
  cef.java_disabled = !web.java_enabled;
  cef.plugins_disabled = !web.plugins_enabled;
  cef.universal_access_from_file_urls_allowed =
      web.allow_universal_access_from_file_urls;
  cef.file_access_from_file_urls_allowed = web.allow_file_access_from_file_urls;
  cef.web_security_disabled = !web.web_security_enabled;
  cef.xss_auditor_enabled = web.xss_auditor_enabled;
  cef.image_load_disabled = !web.loads_images_automatically;
  cef.shrink_standalone_images_to_fit = web.shrinks_standalone_images_to_fit;
  cef.site_specific_quirks_disabled = !web.site_specific_quirks_enabled;
  cef.text_area_resize_disabled = !web.text_areas_are_resizable;
  cef.page_cache_disabled = !web.uses_page_cache;
  cef.tab_to_links_disabled = !web.tabs_to_links;
  cef.hyperlink_auditing_disabled = !web.hyperlink_auditing_enabled;
  cef.user_style_sheet_enabled = web.user_style_sheet_enabled;

  if (!web.user_style_sheet_location.is_empty()) {
    std::string str = web.user_style_sheet_location.spec();
    std::wstring wstr;
    UTF8ToWide(str.c_str(), str.length(), &wstr);
    cef.user_style_sheet_location = cef_string_alloc(wstr.c_str());
  }

  cef.author_and_user_styles_disabled = !web.author_and_user_styles_enabled;
  cef.local_storage_disabled = !web.local_storage_enabled;
  cef.databases_disabled = !web.databases_enabled;
  cef.application_cache_disabled = !web.application_cache_enabled;
  cef.experimental_webgl_enabled = web.experimental_webgl_enabled;
  cef.accelerated_compositing_disabled = !web.accelerated_compositing_enabled;
  cef.accelerated_2d_canvas_disabled = !web.accelerated_2d_canvas_enabled;
}
