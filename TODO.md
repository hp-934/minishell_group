# ✅ Minishell TODO List

## 📦 Modules and Responsibilities

| Module              | Owner       | Status     | Notes                          |
|---------------------|-------------|------------|--------------------------------|
| Prompt & readline   | Alice       | ✅ Done     |                                |
| Signal Handling     | Alice       | 🔄 In Progress | Needs to cover Ctrl+C/D    |
| Parser (quotes, $)  | Bob         | ✅ Done     |                                |
| Heredoc             | Bob         | ⏳ Not Started |                              |
| Pipe Execution      | Alice       | ⏳ Not Started | Waits for parser output     |
| Builtin: cd         | Bob         | ✅ Done     |                                |
| Builtin: exit       | Alice       | ✅ Done     |                                |

## 🔜 This Week’s Goals
- [ ] Complete heredoc implementation
- [ ] Run memory checks with Valgrind
- [ ] Test environment variable expansion edge cases

## 🐞 Known Issues
- Ctrl+C doesn't interrupt heredoc properly
- Exporting empty string doesn’t trigger an error
