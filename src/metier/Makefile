######################################################################
#
# 	Makefile générique
#
# @author :Lucas CHABALIER(chabalierlucas1@gmail.com)
# @date   : 05/02/2015
#
######################################################################


CPP=g++


# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=Src
HEADDIR=Include
LIBDIR=Objet
BINDIR=Bin
DEBUG=yes #yes pour Debug
MSQ=@ # Pour masquer les commandes
MSG=$(MSQ)echo "***"

#Options de compilation
CFLAGS= -std=c++0x -Wall

# L'exécutable
BIN=app

# Où trouver les différents sources *.cpp qu'il faudra compiler pour créer les objets correspondants
SRCPP= $(wildcard $(SRCDIR)/*.cpp)
OBJCPP= $(SRCPP:$(SRCDIR)/%.cpp=$(LIBDIR)/%.o)

# Conditionel du mode Debug
ifeq ($(DEBUG),yes)
	@(MSQ) CFLAGS=$(CFLAGS) -g
	MODE="mode debug"
else
	MODE="mode release"
endif

###############################################################
all: $(BIN)
	$(MSG) "Compilation terminée en" $(MODE)

#Création de l'exécutable
app: $(OBJ) $(OBJCPP)
	$(CPP) -o $(BINDIR)/$@ $^ $(CFLAGS) $(GLLIBS)

################################################################

# Création des différents *.o à partir des *.cpp
$(LIBDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)


################################################################
# Nettoyage des objets => Tout sera recompilé !
clean:
	rm $(LIBDIR)/*.o

# Nettoyage complet => clean + effacement du l'exécutable
mrproper: clean
	rm $(BINDIR)/$(BIN)
