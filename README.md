# Mini-Shell en C

**Mini-shell Unix-like** implémentant les redirections (`< > >>`), pipes (`|`), commandes internes (`cd set`) et prompt dynamique.

## Fonctionnalités

**Prompt** : `hostname:/chemin/courant$`
**Commandes externes** : `ls`, `cat`, `echo`, `ps`, etc. (via PATH)
**Commandes internes** : `cd`, `set`
**Redirections** : `<` (entrée), `>` (sortie), `>>` (append)
**Pipes** : `|` (ls | grep mini)
**Guillemets** : `"hello world"` (un seul argument)
**20 arguments max**, **200 caractères max** par mot

## Structure du projet

```
minishell/
├── main.c          # Boucle principale + prompt
├── lex.c           # Analyseur lexical getlex() (fourni)
├── commande.c      # Parsing + routage 5 cas
├── exec.c          # fork/execvp + redirections/pipes
├── builtins.c      # cd, set
├── lex.h           # Définitions LEX
├── commande.h
├── exec.h
├── builtins.h
├── Makefile        # Compilation automatisée
└── README.md
```


## Installation \& Compilation

### Prérequis

```bash
sudo apt update
sudo apt install build-essential git
```


### Compilation

```bash
make          # ou make all
make clean    # Nettoyer
```


### Exécution

```bash
./minishell
```


## Utilisation

```
ton-pc:/home/user$ ls -la                    # Commande simple
ton-pc:/home/user$ echo "Hello" > fichier.txt # Redirection >
ton-pc:/home/user$ cat < fichier.txt          # Redirection <
ton-pc:/home/user$ echo "Ligne2" >> fichier.txt # Append >>
ton-pc:/home/user$ ls | grep mini             # Pipe
ton-pc:/home/user$ cd /tmp                    # Interne cd
ton-pc:/tmp$ set | head -3                    # Interne set
ton-pc:/tmp$ pwd
/tmp
```


## Tests

| Test | Commande | Résultat attendu |
| :-- | :-- | :-- |
| Simple | `ls -la` | Liste fichiers |
| `>` | `echo test > f` | `f` créé avec "test" |
| `<` | `cat < f` | Affiche "test" |
| `>>` | `echo ligne2 >> f` | `f` = "test\nligne2" |
| `|` | `ps \| grep bash` | Processus bash filtrés |
| `cd` | `cd /tmp ; pwd` | `/tmp` |
| `set` | `set` | Variables d'environnement |

## Détails techniques

### Analyse lexicale

**Automate 4 états** : `Neutre → Spp/Equote/Emot`


### 5 cas implémentés

1. **Simple** : `exec_simple(argv)`
2. **INF** : `dup2(fd_in, 0) → execvp()`
3. **SUP** : `dup2(fd_out, 1) → execvp()`
4. **SPP** : `dup2(fd_app, 1) → execvp()`
5. **TUB** : `pipe() → fork() x2 → execvp() x2`

## Architecture

```
Prompt (gethostname+getcwd)
    ↓
getlex() → commande() → [5 cas]
                        ↓
                   exec_*() → fork/execvp/wait
```

## Licence

Ce projet est sous licence [MIT](LICENSE).


***

**Auteur** : TAS Tom
**Date** : 24 Décembre 2025
**Version** : 1.0.0

