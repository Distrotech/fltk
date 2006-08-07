
DFILES = \
	fl/fl.d \
	fl/box.d \
	fl/boxtype.d \
	fl/color.d \
	fl/color_mac.d \
	fl/draw.d \
	fl/font.d \
	fl/font_mac.d \
	fl/image.d \
	fl/labeltype.d \
	fl/line_style.d \
	fl/rect.d \
	fl/tooltip.d \
	fl/widget.d \
	fl/window.d \
	fl/group.d \
	fl/enumerations.d \
	fl/x.d \
	fl/mac.d

OBJECTS = $(DFILES:.d=.o)

all: hello

hello:  test/hello.o $(OBJECTS)
	echo Linking $@...
	gdc -g -fversion=Apple -framework Carbon $< $(OBJECTS) -o $@
	/Developer/Tools/Rez -t APPL -o $@ fl/macrez.r

.SUFFIXES: .d .fl

.d.o:
	echo Compiling $<...
	gdc -g -fversion=Apple -c $< -o $@

clean:
	rm $(OBJECTS)
	rm test/hello.o


