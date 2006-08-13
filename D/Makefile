
DFILES = \
	fl/fl.d \
	fl/ask.d \
	fl/box.d \
	fl/boxtype.d \
	fl/button.d \
	fl/color.d \
	fl/color_mac.d \
	fl/draw.d \
	fl/font.d \
	fl/font_mac.d \
	fl/image.d \
	fl/input.d \
	fl/input_.d \
	fl/labeltype.d \
	fl/line_style.d \
	fl/rect.d \
	fl/return_button.d \
	fl/shortcut.d \
	fl/tooltip.d \
	fl/widget.d \
	fl/window.d \
	fl/group.d \
	fl/enumerations.d \
	fl/x.d \
	fl/mac.d \
	std/c/osx/qd/quickdraw.d \
	std/c/osx/carbon/carbon.d \
	std/c/osx/carbon/cfstring.d \
	std/c/osx/carbon/cgcontext.d \
	std/c/osx/carbon/types.d \
	std/c/osx/carbon/windowmanager.d

OBJECTS = $(DFILES:.d=.o)

DFLAGS = -g -fbounds-check -funittest -fversion=Apple 

all: message hello button

hello:  test/hello.o $(OBJECTS)
	echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

button:  test/button.o $(OBJECTS)
	echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

message:  test/message.o $(OBJECTS)
	echo Linking $@...
	gdc $(DFLAGS) -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

.SUFFIXES: .d .fl

.d.o:
	echo Compiling $<...
	gdc $(DFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
	rm test/hello.o
	rm test/button.o


