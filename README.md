# Minishell

## 🚀 Project Overview

This project is about recreating a basic Bash-like shell that supports:
- Builtin commands like `cd`, `echo`, `exit`, `export`, `unset`, `env`, `pwd`
- Pipes (`|`)
- Redirections (`<`, `>`, `>>`, `<<`)
- Quoting, environment variable expansion
- Signal handling (e.g., `Ctrl+C`, `Ctrl+D`)

---

## 🧑‍💻 Git Collaboration Workflow (for 2-person teams)

To ensure clean and smooth teamwork, we follow the **branch + pull request (PR)** model when developing.

### ✅ Main Branch (`main`)
- The `main` branch should always be **clean and working**.
- No one should **push directly** to `main`.
- All changes must come through a **Pull Request** (PR).

## 🧭 Before starting any work each day:
- [ ] `git checkout main` – switch to the main branch
- [ ] `git pull origin main` – make sure your local main is up-to-date
- [ ] `git checkout -b your_new_branch` – create your working branch from latest main

### 🛠️ Development Process

1. **Create a Feature or Fix Branch**
```bash
git checkout main
git pull origin main
git checkout -b feature_echo
```

2. **Code and Commit on Your Branch**
```bash
git add .
git commit -m "[builtin] implement echo -n"
git push origin feature_echo
```

3. **Open a Pull Request (PR)**
- On GitHub: click "Compare & pull request"
- Fill out the PR template
- Ask your teammate to review

4. **Review and Merge**
- Your teammate checks your PR
- If it's good, they approve and merge
- You can then delete the feature branch

### 🔄 Keeping Up with `main`
```bash
git checkout feature_echo
git pull origin main
# Fix merge conflicts if needed
git add .
git commit -m "merge main into feature_echo"
```

### 🧯 Best Practices
- Work on separate modules
- Communicate before editing shared files
- Keep PRs small and focused

### ✅ Before Submitting to Vogsphere
```bash
git checkout main
git pull origin main
# Copy this code into your Vogsphere clone directory
```
