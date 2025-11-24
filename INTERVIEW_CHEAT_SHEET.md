# Interview Cheat Sheet - Quick Reference

## Before the Interview

- [ ] Ensure repository is on GitHub
- [ ] Test that Codespaces works
- [ ] Review ANSWER_KEY.md
- [ ] Prepare timer (25-40 minutes)

## Opening (2 minutes)

"Today you'll be debugging a filter management system for an audio interface. 
The README has all the instructions. You'll have about 30 minutes. 
Feel free to think out loud - I'm interested in your process."

## What to Watch For

### Red Flags 🚩
- Doesn't read README or test output
- Makes random changes without understanding
- Can't use basic tools (build, run tests)
- Gives up quickly

### Green Flags ✅
- Reads documentation first
- Runs tests to see the failure
- Analyzes test expectations
- Explains reasoning clearly
- Verifies fix works
- Suggests improvements

## Key Commands They Should Use

```bash
just build      # Or: cmake -B build && cmake --build build
just test       # Or: cd build && ctest --output-on-failure
```

## The Bug Location

File: `src/FilterManager.cpp`, Line 16

```cpp
// WRONG:
bool shouldEnableFilter = (m_sampleRate <= 192000);

// CORRECT:
bool shouldEnableFilter = (m_sampleRate < 192000);
```

## If They Get Stuck (Hints in Order)

1. "What do the test names tell you?" → Focus on 192kHz test
2. "What's the test expecting?" → Filter should be disabled at 192kHz
3. "Where does the sample rate check happen?" → setSampleRate method
4. "Look at the comparison operator" → Should be < not <=

## Discussion Questions (10-15 min)

### Understanding (Required)
- "Walk me through how you found the bug"
- "Why was this happening?"
- "How did you verify the fix?"

### Design (Good to explore)
- "Why do we mute during filter transitions?"
- "What's the purpose of the interface classes?"
- "Why use mock objects in tests?"

### Extensions (For strong candidates)
- "What other test cases might be valuable?"
- "How would you handle hardware errors?"
- "What about thread safety?"
- "Performance considerations?"

## Time Checkpoints

- **5 min**: Should have read README and run tests
- **15 min**: Should have identified the bug location
- **25 min**: Should have fixed and verified
- **30-40 min**: Discussion and wrap-up

## Scoring Guide

### Junior Level
- ✅ Finds bug with hints: **Pass**
- ✅ Finds bug independently: **Strong Pass**
- ❌ Cannot find even with hints: **No Pass**

### Mid Level
- ✅ Finds bug independently in <20 min: **Pass**
- ✅ Finds bug + suggests improvements: **Strong Pass**
- ❌ Needs multiple hints: **Borderline**

### Senior Level
- ✅ Finds bug in <10 min + improvements: **Pass**
- ✅ Finds bug quickly + deep discussion: **Strong Pass**
- ❌ Takes >20 minutes: **Concern**

## Notes Space

Candidate Name: ___________________________
Date: ___________________________

Time to identify bug: _____ minutes
Time to fix bug: _____ minutes
Used hints: Yes / No

Strengths:



Areas for improvement:



Overall: Strong Pass / Pass / Borderline / No Pass
