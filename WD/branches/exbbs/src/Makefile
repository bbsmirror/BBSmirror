# ------------------------------------------------------- #
#  util/Makefile	( NTHU CS MapleBBS Ver 2.36 )	  #
# ------------------------------------------------------- #
#  target : Makefile for ALL				  #
#  create : 95/03/29				 	  #
#  update : 95/12/15				 	  #
# ------------------------------------------------------- #
BBSHOME=/bbs

# freebsd , linux , solaris ... etc. (use by innbbsd)
OSTYPE = freebsd

SUBDIR += lib
SUBDIR += WD
SUBDIR += SO
SUBDIR += util

all:
.for dir in ${SUBDIR}
	@echo "####################"
	@echo "make ${dir}"
	@echo "####################"
	@cd ${dir};make all
.endfor
	@echo "####################"
	@echo "make innbbsd"
	@echo "####################"
	@cd innbbsd;make ${OSTYPE}

install:
.for dir in ${SUBDIR}
	@echo "####################"
	@echo "make ${dir}"
	@echo "####################"
	@cd ${dir};make install
.endfor
	@echo "####################"
	@echo "make innbbsd"
	@echo "####################"
	@cd innbbsd;make ${OSTYPE} install

clean:
.for dir in ${SUBDIR}
	@echo "####################"
	@echo "clean ${dir}"
	@echo "####################"
	@cd ${dir};make clean
.endfor
	@echo "####################"
	@echo "clean innbbsd"
	@echo "####################"
	@cd innbbsd;make clean
