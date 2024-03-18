##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

NAME		:=	arcade
EXT			:=	.cpp

DIR			:=	src
SRC			:=	$(addprefix $(DIR)/,								\
					Main.cpp										\
					Core.cpp										\
				)

LIB_DIR		:=	lib

LIB1_NAME	:=	arcade_ncurses.so
LIB1_DIR	:=	$(LIB_DIR)/ncurses
LIB1_SRC	+=	$(addprefix $(LIB1_DIR)/,							\
					Ncurses.cpp										\
					NcursesKey.cpp									\
				)

LIB2_NAME	:=	arcade_sdl2.so
LIB2_DIR	:=	$(LIB_DIR)/sdl2
LIB2_SRC	+=	$(addprefix $(LIB2_DIR)/,							\
					SDL.cpp											\
				)

LIB3_NAME	:=	lib3.so
LIB3_DIR	:=	$(LIB_DIR)/lib3
LIB3_SRC	+=	$(addprefix $(LIB3_DIR)/,							\
				)

LIB4_NAME	:=	lib4.so
LIB4_DIR	:=	$(LIB_DIR)/lib4
LIB4_SRC	+=	$(addprefix $(LIB4_DIR)/,							\
				)

LIB5_NAME	:=	lib5.so
LIB5_DIR	:=	$(LIB_DIR)/lib5
LIB5_SRC	+=	$(addprefix $(LIB5_DIR)/,							\
				)

FU_DIR		:=	tests/func

UT_DIR		:=	tests/unit
UT_SRC		:=	$(filter-out src/Main.cpp, $(SRC))
UT_SRC		+=	$(addprefix $(UT_DIR)/,								\
				)

DIR_BUILD	:=	build
DIR_BIN		:=	$(DIR_BUILD)/bin

DIR_OBJ		:=	$(DIR_BUILD)/obj
OBJ			:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(SRC))
DEP			:=	$(OBJ:.o=.d)

LIB1_OBJ	:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(LIB1_SRC))
LIB1_DEP	:=	$(LIB1_OBJ:.o=.d)

LIB2_OBJ	:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(LIB2_SRC))
LIB2_DEP	:=	$(LIB2_OBJ:.o=.d)

LIB3_OBJ	:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(LIB3_SRC))
LIB3_DEP	:=	$(LIB3_OBJ:.o=.d)

LIB4_OBJ	:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(LIB4_SRC))
LIB4_DEP	:=	$(LIB4_OBJ:.o=.d)

LIB5_OBJ	:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(LIB5_SRC))
LIB5_DEP	:=	$(LIB5_OBJ:.o=.d)

UT_DIR_OBJ	:=	$(DIR_BUILD)/tests/unit
UT_OBJ		:=	$(patsubst %$(EXT),$(UT_DIR_OBJ)/%.o,$(UT_SRC))
UT_DEP		:=	$(UT_OBJ:.o=.d)

DG_DIR_OBJ	:=	$(DIR_BUILD)/debug
DG_OBJ		:=	$(patsubst %$(EXT),$(DG_DIR_OBJ)/%.o,$(SRC))
DG_DEP		:=	$(DG_OBJ:.o=.d)

DEBUG		:=	$(DIR_BIN)/debug
FU_TEST		:=	$(FU_DIR)/tester.sh
UT_TEST		:=	$(DIR_BIN)/unit_test

RM			:=	rm -rf

CXX			:=	g++
LD			:=	ld -shared
CXXFLAGS	:=	-std=c++20 -iquote. -Wall -Wextra -fPIC -lncurses

all:				core graphicals games

define CREATE_DIR
	@if [ ! -d $(dir $@) ]; then									\
		mkdir -p $(dir $@) 											\
		&& printf "\033[93m[CREATED]\033[0m %s\n" $(dir $@)			\
		|| printf "\033[31m[ERROR]\033[0m %s\n"   $(dir $@);		\
	fi
endef

$(DIR_BUILD)/:		; $(CREATE_DIR)

define BUILD_OBJ
	@$(RM) $(patsubst %.o,%.gcda,$@)
	@$(RM) $(patsubst %.o,%.gcno,$@)
	$(CREATE_DIR)
	@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@							\
	&& printf "\033[32m[OK]\033[0m %s\n" $<							\
	|| printf "\033[31m[KO]\033[0m %s\n" $<
endef

$(DIR_OBJ)/%.o:		%$(EXT); $(BUILD_OBJ)
$(UT_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)
$(DG_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)

define COMPILE
	$(CREATE_DIR)
	@$(CXX) $(CXXFLAGS) -o $@ $^			 						\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@						\
	|| printf "\033[31m[ERROR]\033[0m %s\n"  $@
endef

define COMPILE_LIB
	$(CREATE_DIR)
	@$(LD) -o $@ $^						 							\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@						\
	|| printf "\033[31m[ERROR]\033[0m %s\n"  $@
endef

-include $(DEP)
$(NAME):			$(OBJ); 	$(COMPILE)
core:				$(NAME)

-include $(LIB1_DEP)
$(LIB1_NAME):		$(LIB1_OBJ);	$(COMPILE_LIB)
-include $(LIB2_DEP)
$(LIB2_NAME):		$(LIB2_OBJ);	$(COMPILE_LIB)
-include $(LIB3_DEP)
$(LIB3_NAME):		$(LIB3_OBJ);	$(COMPILE_LIB)
graphicals:			 $(LIB1_NAME) $(LIB2_NAME) $(LIB3_NAME)

-include $(LIB4_DEP)
$(LIB4_NAME):		$(LIB4_OBJ);	$(COMPILE_LIB)
-include $(LIB5_DEP)
$(LIB5_NAME):		$(LIB5_OBJ);	$(COMPILE_LIB)
games:				$(LIB4_NAME) $(LIB5_NAME)

tests_functional:	$(FU_TEST) $(NAME)
	@$^

-include $(UT_DEP)
$(UT_TEST):			CXXFLAGS += -lcriterion --coverage
$(UT_TEST):			$(UT_OBJ);	$(COMPILE)
tests_unit:			$(UT_TEST)
	@cp $(UT_TEST) $(UT_DIR_OBJ)
	@$(UT_DIR_OBJ)/$(notdir $<)

-include $(DG_DEP)
$(DEBUG):			CXXFLAGS += -g
$(DEBUG):			$(DG_OBJ); 	$(COMPILE)
debug:				$(DEBUG)

tests_run:			tests_functional tests_unit
	gcovr $(UT_DIR_OBJ) --exclude tests/
	gcovr $(UT_DIR_OBJ) --exclude tests/ --branches

doc:				$(DIR_BUILD)/
	doxygen docs/Doxyfile
	python -m webbrowser -t build/docs/index.html >/dev/null

clean:
	@[ -d $(DIR_BUILD) ]											\
	&& $(RM) $(DIR_BUILD)											\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(DIR_BUILD) || true

fclean:				clean
	for bin in $(NAME) $(LIB1_NAME) $(LIB2_NAME)					\
			   $(LIB3_NAME) $(LIB4_NAME) $(LIB5_NAME); do 			\
		[ -f $$bin ]												\
		&& $(RM) $$bin												\
		&& printf "\033[31m[DELETED]\033[0m %s\n" $$bin || true;	\
	done

re:					fclean all

.PHONY:				all tests tests_run debug clean fclean re doc

.SILENT:			all tests tests_run debug clean fclean re doc
