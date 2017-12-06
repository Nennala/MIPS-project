#####################################
# Auteur : Daphné Porteries
# Date de création : 13/07/2017
# Dernière modification : 06/12/2017
#####################################

# Nom des dossiers pour les headers, les sources et les objets
SRCDIR=src
HEADDIR=header
OBJDIR=obj
BINDIR=bin

# Variables de compilations
CC=gcc
DEBUG = yes

# Flags pour les librairies et la compilation
LDFLAGS= -lm

ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -ggdb -I$(HEADDIR) -O0
else
	CFLAGS = -I$(HEADDIR) -O2
endif

# Position des sources
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXEC = mips
MAIN = main

all : $(EXEC)

# Création executable
$(EXEC) : $(OBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)

# Création des différents .o à l'aide des .c
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
# Création de main.o, sans cette recette ne se crée pas
$(OBJDIR)/main.o : $(SRCDIR)/$(MAIN).c $(HEADDIR)/*.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

# Nettoyage des objet => permet de tout recompiler
clean :
	rm -f $(OBJDIR)/*.o

# Nettoyage complet => clean + effacement de l'executable
mrproper : clean
	rm -f $(BINDIR)/*


