# Setting Up the Interview Test on GitHub

## Quick Setup Steps

### 1. Create a New GitHub Repository

```bash
cd /Users/ross.chisholm/Code/Interview
git init
git add .
git commit -m "Initial commit: Audio Filter Manager technical test"
```

Then create a new repository on GitHub and push:

```bash
git remote add origin https://github.com/YOUR_ORG/audio-filter-interview.git
git branch -M main
git push -u origin main
```

### 2. Enable GitHub Codespaces

GitHub Codespaces will work automatically thanks to the `.devcontainer/devcontainer.json` configuration.

When a candidate opens the repository in Codespaces:
1. The C++ development environment will be automatically configured
2. CMake, build tools, and Just will be pre-installed
3. Catch2 will be downloaded automatically during the first build

### 3. Test Instructions for Candidates

Share this repository link with candidates along with these instructions:

#### For Remote Interviews

1. Click the "Code" button on the GitHub repository
2. Select "Codespaces" tab
3. Click "Create codespace on main"
4. Wait for the environment to load (1-2 minutes)
5. Open a terminal in VS Code
6. Run `just test` to see the failing tests
7. Fix the bug and verify with `just test`

#### For In-Person Interviews

1. Clone the repository:
   ```bash
   git clone https://github.com/YOUR_ORG/audio-filter-interview.git
   cd audio-filter-interview
   ```

2. Build and test:
   ```bash
   just build
   just test
   ```

### 4. Repository Settings

Consider these settings for the interview repository:

- **Make it private** - Prevent candidates from sharing solutions
- **Template repository** - Create a template so you can easily generate new instances for each candidate
- **Branch protection** - Disable for interview repos (candidates need to push)

### 5. Multiple Candidates

For each candidate, either:

**Option A: Fresh Codespace (Recommended)**
- Each candidate creates their own Codespace
- No interference between candidates
- Automatic cleanup after interview

**Option B: Separate Branches**
```bash
git checkout -b candidate-john-doe
git push -u origin candidate-john-doe
```

### 6. Reviewing Candidate Solutions

After the interview:

```bash
# If using Codespaces, have them create a branch
git checkout -b solution-candidate-name

# Or download their changes
git diff > candidate-solution.patch
```

## Additional Tips

### Time Management

Set up a timer and mention these time expectations:
- Reading and understanding: 5 minutes
- Debugging and fixing: 10-20 minutes
- Discussion: 10-15 minutes
- **Total: 25-40 minutes**

### Observation Points

Watch for:
- Do they read the README first?
- Do they run the tests immediately?
- Do they read the test output carefully?
- Do they understand the mock objects?
- Do they verify their fix works?

### Follow-up Questions

After they fix the bug, ask:
1. "Walk me through how you found the bug"
2. "How would you prevent this bug in the future?"
3. "What other improvements would you suggest?"
4. "How would you test this on real hardware?"

## Troubleshooting

### Build Issues

If candidates have build issues:
```bash
just clean
just build
```

### Codespaces Not Loading

Ensure `.devcontainer/devcontainer.json` is in the repository root.

### Just Not Found

Fallback to CMake directly:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
cd build && ctest --output-on-failure
```

## Solution Variations

Some candidates might:
- Change `<=` to `<` (correct)
- Change the logic entirely (acceptable if tests pass)
- Add additional validation (bonus points)
- Refactor the code (good initiative)

All are valid as long as:
✅ All tests pass
✅ Code is readable
✅ They can explain their reasoning
