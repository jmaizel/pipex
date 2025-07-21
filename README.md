
# 🔗 pipex

> _"Recreating the magic of Unix pipes."_

---

## 🇫🇷 Version Française

### 🎯 Objectif

`pipex` est un projet qui vous fait découvrir les **pipes UNIX** en profondeur. L'objectif est de recréer le comportement de redirection de la ligne de commande suivante :

```bash
< file1 cmd1 | cmd2 > file2
```

Votre programme doit se lancer ainsi :

```bash
./pipex file1 cmd1 cmd2 file2
```

### 🧱 Fonctionnalités

- Redirection de fichiers (`<`, `>`)
- Exécution de deux commandes en **pipeline**
- Recherche du chemin des commandes via `PATH`
- Gestion des erreurs système
- Gestion des **processus** (`fork`, `execve`, `pipe`, etc.)
- Respect strict de la **norme C 42**
- Pas de fuites mémoire

### 💡 Exemples

```bash
./pipex infile "ls -l" "wc -l" outfile
# Équivaut à : < infile ls -l | wc -l > outfile

./pipex infile "grep hello" "wc -w" outfile
# Équivaut à : < infile grep hello | wc -w > outfile
```

### 🛠️ Technologies

- **Langage :** C
- **Librairie autorisée :** Libft
- **Fonctions autorisées :** open, close, read, write, malloc, free, access, dup, dup2, execve, fork, pipe, etc.
- **Compilation :** Makefile (`all`, `clean`, `fclean`, `re`, `bonus`)

### ✨ Bonus possibles

- Support de **plusieurs pipes** (ex : cmd1 | cmd2 | cmd3 ...)
- Gestion du mode **here_doc** (limiteur + redirection append)

### 📁 Structure du projet

```
pipex/
├── src/
├── include/
├── libft/
├── Makefile
└── README.md
```

### 🧠 Compétences développées

- Gestion de processus et de redirections UNIX
- Parsing et exécution de commandes shell
- Compréhension de l’environnement système
- Gestion propre des erreurs et de la mémoire

---

## 🇬🇧 English Version

### 🎯 Objective

`pipex` is a project designed to teach you how **UNIX pipes** work internally. You must recreate the behavior of the following shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

Your program must be run like this:

```bash
./pipex file1 cmd1 cmd2 file2
```

### 🧱 Features

- Input/output file redirection
- Executes two shell commands in a pipeline
- Resolves full path using `PATH`
- Proper error handling
- **Process management** with `fork`, `pipe`, `execve`, etc.
- Must follow **42 coding standards**
- No memory leaks allowed

### 💡 Examples

```bash
./pipex infile "ls -l" "wc -l" outfile
# Same as: < infile ls -l | wc -l > outfile

./pipex infile "grep hello" "wc -w" outfile
# Same as: < infile grep hello | wc -w > outfile
```

### 🛠️ Tech Stack

- **Language:** C
- **Allowed libs:** Libft
- **Syscalls used:** open, read, write, fork, execve, pipe, dup2, etc.
- **Build:** Makefile with rules (`all`, `clean`, `fclean`, `re`, `bonus`)

### ✨ Bonus Features

- Handle **multiple pipes** (e.g., cmd1 | cmd2 | cmd3 ...)
- Implement **here_doc** feature (limiter + append redirection)

### 📁 Project Structure

```
pipex/
├── src/
├── include/
├── libft/
├── Makefile
└── README.md
```

### 🧠 Skills Gained

- Mastery of UNIX processes and file descriptors
- Parsing and executing shell-like commands
- System-level debugging and error handling
- Clean memory management and robust architecture

