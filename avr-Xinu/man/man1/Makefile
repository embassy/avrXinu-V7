$(NROFF)#
#  Make Xinu Manual Pages - only FILES change between man[01234]
#

DIR	=	../..
MACROS	=	$(DIR)/lib/tmac.an
NROFF = groff -Thtml

.SUFFIXES:	.ms .html .1 .2 .3 .4

.ms.html:
		$(NROFF) -ms $< > ,$* ; mv ,$* $*.html

.1.html:
		$(NROFF) $(MACROS) $< > ,$* ; mv ,$* $*.1.html

.2.html:
		$(NROFF) $(MACROS) $< > ,$* ; mv ,$* $*.2.html

.3.html:
		$(NROFF) $(MACROS) $< > ,$* ; mv ,$* $*.3.html

.4.html:
		$(NROFF) $(MACROS) $< > ,$* ; mv ,$* $*.4.html

FILES	=	$(MACROS)	\
		Intro1.html	\
		fs.html

all:		$(FILES)

install:
		@echo no installation possible - use "'make print'"

clean:
		rm -rf *.html core ,*

Intro1.html:	Intro1.1
		$(NROFF) -man Intro1.1 > ,Intro1 ; mv ,Intro1 Intro1.html

Intro2.html:	Intro2.2
		$(NROFF) -man Intro2.2 > ,Intro2 ; mv ,Intro2 Intro2.html

Intro3.html:	Intro3.3
		$(NROFF) -man Intro3.3 > ,Intro3 ; mv ,Intro3 Intro3.html

Intro4.html:	Intro4.4
		$(NROFF) -man Intro4.4 > ,Intro4 ; mv ,Intro4 Intro4.html

print:		listings

listings:	$(FILES)
#		cat *.html | sed '1,2d;s/^/	/' | lpr
