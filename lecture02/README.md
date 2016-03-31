# Lecture 2 - Introduction to Git

## Demo 1

Configure global settings, initialize a Git repo, add files, commit changes,
and view history log.

```
$ git config --global user.name "Jane Doe"
$ git config --global user.email janedoe@example.com
$ git config --global core.editor emacs  # (or vim or nano)
$ git config --list
$ less ~/.gitconfig

(make a directory and navigate into it)

$ git init
$ git status
$ git log

(make a file README.md and write some text)

$ git status
$ git add README.md
$ git status
$ git commit

(Write a commit message, save, and exit.)
```

Aside: A good commit message makes it easy for collaborators to understand
what this commit does. Here is a good template to follow:

```
Short (50 chars or less) summary of changes

More detailed explanatory text, if necessary.  Wrap it to
about 72 characters or so.  In some contexts, the first
line is treated as the subject of an email and the rest of
the text as the body.  The blank line separating the
summary from the body is critical (unless you omit the body
entirely); tools like rebase can get confused if you run
the two together.

Further paragraphs come after blank lines.

  - Bullet points are okay, too

  - Typically a hyphen or asterisk is used for the bullet,
    preceded by a single space, with blank lines in
    between, but conventions vary here

If you use an issue tracker, put references to them at the bottom,
like this:

Resolves: #123
See also: #456, #789
```
See http://chris.beams.io/posts/git-commit/ for a lengthy discussion on what
makes a good commit message.)

Back to the demo:

```
$ git status
$ git log

(Make additional changes to README.md. Delete something and add something else.)

$ git status
$ git diff
$ git commit
```

## Demo 2

* Create a new repo on GitHub
* **Option #1:** do not initialize with `README.md`. Follow instructions to
  add remotes.
* **Option #2:** initialize with a `README.md`. **HOWEVER**, this repo's commit
  history is now fully incompatible with whatever you already have, if anything.
  Best is to clone, manually copy files, commit, and push.

(Assume we follow Option 1.)

* Refresh and look at GitHub version.

```
$ git remote add origin https://github.com/yourgitusername/thereponame.git
$ git remote -v
$ git push -u origin master
$ git status

(Make some more changes.)

$ git status
$ git add (changes)
$ git commit
$ git push origin  # (current default is "origin")
```

## Demo 3

Branching.

```
$ git branch
$ git branch iss53
$ git branch
$ git checkout iss53
$ git branch
$ git log --decorate --all

(create new file, add, status, commit)

$ git log
$ git log --decorate --all
$ git checkout master
$ git branch hotfix
$ git checkout hotfix

(edit existing file, add, status, commit)

$ git log
$ git log --decorate --all
$ git log --decorate --all --graph
$ git log --decorate --all --graph --oneline
```

## Demo 4

Merging

```
$ git checkout master
$ git merge hotfix
$ git log
$ git log --decorate --all --graph --oneline
$ git branch -d hotfix
$ git log --decorate --all --graph --oneline
$ git checkout iss53

(make changes, add, status, commit)

$ git log
$ git log --decorate --all --graph --oneline
$ git checkout master
$ git merge iss53
$ git log --decorate --all --graph --oneline
$ git branch -d iss53
$ git log --decorate --all --graph --oneline
$ git push origin
$ git log --decorate --all --graph --oneline
```

## Demo 5

* Fork, clone, branch, edit, push branch, initiate pull request.
