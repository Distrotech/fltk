
ALL = buttons
#ALL = arc menubar message boxtype hello button

all: $(ALL) 


DFILES = \
	fl/abort.d \
	fl/add_idle.d \
	fl/adjuster.d \
	fl/arc.d \
	fl/arg.d \
	fl/ask.d \
	fl/bitmap.d \
	fl/bmp_image.d \
	fl/box.d \
	fl/boxtype.d \
	fl/browser.d \
	fl/browser_.d \
	fl/browser_load.d \
	fl/button.d \
	fl/call_main.d \
	fl/chart.d \
	fl/check_browser.d \
	fl/check_button.d \
	fl/choice.d \
	fl/clock.d \
	fl/cmap.d \
	fl/color.d \
	fl/color_chooser.d \
	fl/color_mac.d \
	fl/color_win32.d \
	fl/compose.d \
	fl/counter.d \
	fl/cursor.d \
	fl/curve.d \
	fl/dial.d \
	fl/diamond_box.d \
	fl/dirent.d \
	fl/display.d \
	fl/dnd.d \
	fl/dnd_mac.d \
	fl/dnd_win32.d \
	fl/dnd_x.d \
	fl/double_window.d \
	fl/draw.d \
	fl/draw_image.d \
	fl/draw_image_mac.d \
	fl/draw_image_win32.d \
	fl/draw_pixmap.d \
	fl/dump_compose.d \
	fl/encoding_latin1.d \
	fl/encoding_mac_roman.d \
	fl/engraved_label.d \
	fl/enumerations.d \
	fl/export.d \
	fl/fastarrow.d \
	fl/file_browser.d \
	fl/file_chooser.d \
	fl/file_chooser2.d \
	fl/file_dir.d \
	fl/file_icon.d \
	fl/file_icon2.d \
	fl/file_input.d \
	fl/filename.d \
	fl/filename_absolute.d \
	fl/filename_expand.d \
	fl/filename_ext.d \
	fl/filename_isdir.d \
	fl/filename_list.d \
	fl/filename_match.d \
	fl/filename_setext.d \
	fl/fill_dial.d \
	fl/fill_slider.d \
	fl/fl.d \
	fl/float_input.d \
	fl/flstring.d \
	fl/font.d \
	fl/font_mac.d \
	fl/font_win32.d \
	fl/font_x.d \
	fl/font_xft.d \
	fl/forms.d \
	fl/forms_bitmap.d \
	fl/forms_compatability.d \
	fl/forms_free.d \
	fl/forms_fselect.d \
	fl/forms_pixmap.d \
	fl/forms_timer.d \
	fl/formsbitmap.d \
	fl/formspixmap.d \
	fl/free.d \
	fl/get_key.d \
	fl/get_key_mac.d \
	fl/get_key_win32.d \
	fl/get_system_colors.d \
	fl/gif_image.d \
	fl/gl.d \
	fl/gl2opengl.d \
	fl/gl_choice.d \
	fl/gl_draw.d \
	fl/gl_overlay.d \
	fl/gl_start.d \
	fl/gl_window.d \
	fl/glut.d \
	fl/glut_compatability.d \
	fl/glut_font.d \
	fl/grab.d \
	fl/group.d \
	fl/help_dialog.d \
	fl/help_view.d \
	fl/hold_browser.d \
	fl/hor_fill_slider.d \
	fl/hor_nice_slider.d \
	fl/hor_slider.d \
	fl/hor_value_slider.d \
	fl/image.d \
	fl/images_core.d \
	fl/input.d \
	fl/input_.d \
	fl/input_choice.d \
	fl/int_input.d \
	fl/jpeg_image.d \
	fl/labeltype.d \
	fl/light_button.d \
	fl/line_dial.d \
	fl/line_style.d \
	fl/lock.d \
	fl/mac.d \
	fl/math.d \
	fl/mediumarrow.d \
	fl/menu.d \
	fl/menu_.d \
	fl/menu_add.d \
	fl/menu_bar.d \
	fl/menu_button.d \
	fl/menu_global.d \
	fl/menu_item.d \
	fl/menu_rar.d \
	fl/menu_window.d \
	fl/message.d \
	fl/multi_browser.d \
	fl/multi_label.d \
	fl/multiline_input.d \
	fl/multiline_output.d \
	fl/nice_slider.d \
	fl/numericsort.d \
	fl/object.d \
	fl/output.d \
	fl/oval_box.d \
	fl/overlay.d \
	fl/overlay_visual.d \
	fl/overlay_window.d \
	fl/own_colormap.d \
	fl/pack.d \
	fl/pixmap.d \
	fl/plastic.d \
	fl/png_image.d \
	fl/pnm_image.d \
	fl/positioner.d \
	fl/preferences.d \
	fl/progress.d \
	fl/radio_button.d \
	fl/radio_light_button.d \
	fl/radio_round_button.d \
	fl/read_image.d \
	fl/read_image_mac.d \
	fl/read_image_win32.d \
	fl/rect.d \
	fl/repeat_button.d \
	fl/return_button.d \
	fl/roller.d \
	fl/round_box.d \
	fl/round_button.d \
	fl/round_clock.d \
	fl/rounded_box.d \
	fl/scandir.d \
	fl/scandir_win32.d \
	fl/screen_xywh.d \
	fl/scroll.d \
	fl/scroll_area.d \
	fl/scrollbar.d \
	fl/secret_input.d \
	fl/select_browser.d \
	fl/set_font.d \
	fl/set_fonts.d \
	fl/set_fonts_mac.d \
	fl/set_fonts_win32.d \
	fl/set_fonts_x.d \
	fl/set_fonts_xft.d \
	fl/shadow_box.d \
	fl/shared_image.d \
	fl/shortcut.d \
	fl/show_colormap.d \
	fl/show_input.d \
	fl/simple_counter.d \
	fl/single_window.d \
	fl/slider.d \
	fl/slowarrow.d \
	fl/spinner.d \
	fl/symbols.d \
	fl/sys_menu_bar.d \
	fl/tabs.d \
	fl/text_buffer.d \
	fl/text_display.d \
	fl/text_editor.d \
	fl/tile.d \
	fl/tiled_image.d \
	fl/timer.d \
	fl/toggle_button.d \
	fl/toggle_light_button.d \
	fl/toggle_round_button.d \
	fl/tooltip.d \
	fl/valuator.d \
	fl/value_input.d \
	fl/value_output.d \
	fl/value_slider.d \
	fl/vertex.d \
	fl/visual.d \
	fl/vsnprintf.d \
	fl/widget.d \
	fl/win32.d \
	fl/window.d \
	fl/window_fullscreen.d \
	fl/window_hotspot.d \
	fl/window_iconize.d \
	fl/wizard.d \
	fl/x.d \
	fl/xbm_image.d \
	fl/xcolor.d \
	fl/xpm_image.d \
	std/c/osx/qd/quickdraw.d \
	std/c/osx/carbon/carbon.d \
	std/c/osx/carbon/cfstring.d \
	std/c/osx/carbon/cgcontext.d \
	std/c/osx/carbon/types.d \
	std/c/osx/carbon/windowmanager.d

OBJECTS = $(DFILES:.d=.o)

DFLAGS = -g -fbounds-check -funittest -fversion=__APPLE__


arc:  test/arc.o $(OBJECTS)
	@ echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

boxtype:  test/boxtype.o $(OBJECTS)
	@ echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

button:  test/button.o $(OBJECTS)
	@ echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

buttons:  test/buttons.o $(OBJECTS)
	@ echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

hello:  test/hello.o $(OBJECTS)
	@ echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

menubar:  test/menubar.o $(OBJECTS)
	@ echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

message:  test/message.o $(OBJECTS)
	@ echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r


.SUFFIXES: .d .fl .o

.d.o:
	@ echo Compiling $<...
	gdc $(DFLAGS) -c $< -o $@

clean:
	rm -f fl/*.o
	rm -f std/c/osx/*/*.o
	rm -f test/*.o
	rm -f $(ALL)


