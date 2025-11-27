# Audio Filter Manager - Interviewer Guide

## Before the Interview

- [ ] Ensure repository is on GitHub and made public for the candidate to create a codespace from
- [ ] Test that Codespaces works
- [ ] Review this guide
- [ ] Prepare timer (30 minutes for all tasks)

## Opening Script (2 minutes)

> "Today you'll be working on a filter management system for an audio interface. There are multiple tasks to work through sequentially. The README has all the instructions. You'll have about 30 minutes total. Feel free to think out loud - I'm interested in your process and you can ask me any questions throughout."

---

## Overview of Tasks

The interview consists of three sequential tasks:

1. **Task 1: Fix the failing tests** (~5-10 minutes)
   - Fix a bug in the sample rate comparison logic
   
2. **Task 2: Implement muting functionality** (~10-15 minutes)
   - Add mute/unmute around filter state changes
   
3. **Task 3: Add hardware-specific muting delay** (~15-20 minutes)
   - Implement configurable unmute delay (e.g., 2 seconds for some hardware)
   - Add tests for the new functionality

4. **Bonus: Additional improvements** (~5-10 minutes)

---

## Task 1: Fix the Failing Tests

### Location
**File:** `src/FilterManager.cpp`, **Line 18**

### Current (Buggy) Code
```cpp
// Make sure filter is disabled at 96kHz
m_shouldFilterBeEnabled = (m_sampleRate <= 192000);
```

### The Problem
1. **Wrong comparison operator:** Uses `<=` instead of `<`
2. **Wrong comment:** Says "96kHz" but should say "192kHz"

### The Fix
```cpp
// Make sure filter is disabled at 192kHz and above
m_shouldFilterBeEnabled = (m_sampleRate < 192000);
```

### Why This is a Bug

**Specification:** The filter should only be enabled at sample rates **below 192kHz**

**Current behavior:**
- ✅ 44.1kHz → filter enabled (correct)
- ✅ 48kHz → filter enabled (correct)
- ✅ 96kHz → filter enabled (correct)
- ❌ **192kHz → filter enabled (WRONG - should be disabled)**
- ✅ 384kHz → filter disabled (correct)

**After fix:**
- ✅ 192kHz → filter disabled (correct)

---

## Expected Candidate Approach

A good candidate should:

1. **Read the README** - Understand the problem context
2. **Run the tests** - Use `just test` to see the failure
3. **Analyze the failing test** - Read test output carefully
4. **Locate the bug** - Find the comparison in `FilterManager.cpp`
5. **Fix the bug** - Change `<=` to `<`
6. **Fix the comment** - Update "96kHz" to "192kHz"
7. **Verify the fix** - Run `just test` again to confirm all pass

### Key Commands
```bash
just build      # Build the project
just test       # Run tests (shows failure)
just debug      # Get debugging instructions
```

---

## What to Watch For

### 🚩 Red Flags
- Doesn't read README or test output
- Makes random changes without understanding
- Can't use basic build/test commands
- Gives up quickly
- Doesn't verify the fix works
- Ignores the misleading comment

### ✅ Green Flags
- Reads documentation first
- Runs tests immediately to see failure
- Analyzes test expectations carefully
- Explains reasoning clearly
- Uses debugger or print statements effectively
- Notices and fixes the comment
- Verifies fix works
- Suggests improvements or additional test cases

---

## If They Get Stuck - Progressive Hints

Use judgment on timelines to prompt here.

### Hint 1 (5 minutes in, if stuck)
> "What do the test names tell you about what's expected?"
→ Focus them on the 192kHz test

### Hint 2 (10 minutes in, still stuck)
> "What's the test expecting at 192kHz? Is that what's happening?"
→ Filter should be disabled at 192kHz

### Hint 3 (15 minutes in, still stuck)
> "Where in the code does the sample rate check happen?"
→ Point them to `setSampleRate` method

### Hint 4 (20 minutes in, last resort)
> "Look carefully at the comparison operator on line 18"
→ Should be `<` not `<=`

---

## Task 2: Implement Muting Functionality

### Requirements
The DSP should mute/unmute during filter state changes to prevent audio artifacts:
1. Call `mute()` before changing filter state
2. Call `unmute()` after changing filter state
3. Only do this when the filter state actually changes (not on every call)

### Expected Implementation Location
**File:** `src/FilterManager.cpp`, in `applyFilterState()` method

### Current Code (Incomplete)
```cpp
void FilterManager::applyFilterState(bool enable) 
{
    // Apply the hardware change
    if (enable) {
        m_hardware.enableFilter();
    } else {
        m_hardware.disableFilter();
    }
    
    // Update our internal state
    m_filterEnabled = enable;
}
```

### Expected Solution
```cpp
void FilterManager::applyFilterState(bool enable) 
{
    // Mute to prevent clicks/pops
    m_dsp.mute();
    
    // Apply the hardware change
    if (enable) {
        m_hardware.enableFilter();
    } else {
        m_hardware.disableFilter();
    }
    
    // Update our internal state
    m_filterEnabled = enable;
    
    // Unmute after transition complete
    m_dsp.unmute();
}
```

### What to Look For
- ✅ Adds `mute()` before hardware change
- ✅ Adds `unmute()` after hardware change
- ✅ Runs tests to verify functionality
- ✅ Tests are in the "mutes during transitions" test case

### Common Mistakes
- ❌ Muting on every call instead of just in `applyFilterState()`
- ❌ Not understanding when `applyFilterState()` is called
- ❌ Forgetting to unmute

---

## Task 3: Add Hardware-Specific Muting Delay

### Requirements
1. Some hardware needs a delay before unmuting (e.g., 2 seconds)
2. Should be configurable for different products
3. Assume client code can manage time (e.g., via callbacks or timers)
4. Should allow for other time periods in the future
5. Must add tests for this functionality

### Expected Design Approach

There are multiple valid approaches. Strong candidates might suggest:

#### Option A: Callback-Based (Preferred)
Add a callback that's invoked when unmuting should happen:

```cpp
// In FilterManager.h
using UnmuteCallback = std::function<void(std::function<void()>, uint32_t)>;

class FilterManager {
public:
    FilterManager(IHardwareInterface& hardware, IDspInterface& dsp, 
                  UnmuteCallback unmuteCallback = nullptr);
    
    void setUnmuteDelay(uint32_t delayMs);
    
private:
    UnmuteCallback m_unmuteCallback;
    uint32_t m_unmuteDelay;
};
```

Usage:
```cpp
// Client provides a way to schedule unmute after delay
auto unmuteCallback = [](std::function<void()> action, uint32_t delayMs) {
    // Schedule action to run after delayMs
    timer.schedule(action, delayMs);
};
```

#### Option B: Deferred Unmute
Separate the unmute into a deferred call:

```cpp
// In FilterManager.h
class FilterManager {
public:
    void setUnmuteDelay(uint32_t delayMs);
    void completeUnmute(); // Call this after delay
    
private:
    uint32_t m_unmuteDelay;
    bool m_pendingUnmute;
};
```

#### Option C: Time-Based Interface
Add time tracking to the interface:

```cpp
// In FilterManager.h
class FilterManager {
public:
    void setUnmuteDelayMs(uint32_t delayMs);
    void update(uint32_t currentTimeMs); // Called regularly by client
    
private:
    uint32_t m_unmuteDelay;
    uint32_t m_unmuteScheduledTime;
    bool m_awaitingUnmute;
};
```

### What to Look For

#### Design Quality
- ✅ Recognizes need for external time management
- ✅ Creates extensible API (not hardcoded to 2 seconds)
- ✅ Maintains backward compatibility (e.g., default = 0 delay)
- ✅ Considers thread safety implications

#### Implementation Quality
- ✅ Clean API design
- ✅ Proper encapsulation
- ✅ Handles edge cases (e.g., multiple rapid calls)

#### Testing
- ✅ Adds test cases for delayed unmute
- ✅ Tests immediate unmute (0 delay) still works
- ✅ Tests different delay values
- ✅ Uses mocks to verify timing

### Discussion Points for Task 3
- "Walk me through your design decision"
- "Why did you choose this approach over alternatives?"
- "How would a client use this API?"
- "What happens if the filter state changes again before unmuting?"
- "How would you test this with real hardware?"

---

## Overall Time Checkpoints

| Time | Expected Progress |
|------|-------------------|
| **5 min** | Read README, run tests |
| **10 min** | Complete Task 1 (fix bug) |
| **10 min** | Complete Task 2 (add muting) |
| **10 min** | Complete Task 3 (delayed unmute design + implementation) |
| **10 min** | Discussion and wrap-up |

---

## Discussion Questions (Final 10 minutes)

Accept answers if they came up naturally in the interview. Pick and choice questions below to based on candidate and areas you want to validate.

### Understanding (Required - Ask All Candidates)
1. "Walk me through how you found the bug"
2. "Why was the filter enabling at 192kHz?"
3. "How did you verify your fix worked?"
4. "Did you notice anything else wrong?" (looking for the comment fix)

### Design (Good for Mid-Level+)
1. "Why do we have two separate interfaces (Hardware and DSP)?"
2. "What's the purpose of the `m_userRequestedState` variable?"
3. "Why use mock objects in the tests?"
4. "What happens if someone calls `setFilterEnabled(true)` at 192kHz?"

### Code Quality (For Strong Candidates)
1. "Are there any other potential issues with this code?"
2. "How would you handle edge cases (e.g., 0 Hz sample rate)?"
3. "What if hardware operations could fail?"
4. "Is this code thread-safe? Should it be?"

### Extensions (For Senior Candidates)
1. "What other test cases might be valuable?"
2. "How would you test this with real hardware?"
3. "What performance considerations are there?"
4. "How would you extend this to support multiple filters?"
5. "Would you change the API design? Why or why not?"

---

## Scoring Guide

This is a guideline - to be validated in interviews and updated.

### Junior Developer

**Focus:** Can they complete Tasks 1 and 2?

| Tasks Completed | Time | Quality | Outcome |
|-----------------|------|---------|---------|
| Tasks 1 + 2 | <30 min | Good | **Borderline** |
| Tasks 1 + 2 | <20 min | Good | **Pass** |
| Tasks 1,2, + 3 | <30 min | Good | **Strong Pass** |
| Cannot complete Task 1 | - | - | **No Pass** |

**Key Indicators:**
- ✅ Can debug systematically
- ✅ Understands test output
- ✅ Writes clean, working code
- ⚠️ Task 3 is stretch goal for juniors

### Mid-Level Developer

**Focus:** Should complete Tasks 1, 2, and start Task 3

| Tasks Completed | Time | Quality | Outcome |
|-----------------|------|---------|---------|
| Tasks 1 + 2 | <30 min | Good | **Pass** |
| Tasks 1 + 2 + 3 (partial) | <50 min | Good design thinking | **Pass** |
| Tasks 1 + 2 + 3 (complete) | <55 min | Clean implementation | **Strong Pass** |
| Only Task 1 | >30 min | - | **Concern** |

**Key Indicators:**
- ✅ Completes Tasks 1 & 2 independently
- ✅ Understands design tradeoffs in Task 3
- ✅ Can articulate different approaches
- ✅ Writes maintainable code
- ✅ Adds appropriate tests

### Senior Developer

**Focus:** Should complete all tasks with high quality

| Tasks Completed | Time | Quality | Outcome |
|-----------------|------|---------|---------|
| Tasks 1 + 2 + 3 | <20 min | Excellent design + tests | **Pass** |
| Tasks 1 + 2 + 3 + Bonus | <30 min | Production-ready code | **Strong Pass** |
| All tasks + deep insights | <40 min | Architecture discussion | **Excellent** |
| Missing Task 3 | - | - | **Concern** |

**Key Indicators:**
- ✅ Completes all tasks efficiently
- ✅ Excellent API design for Task 3
- ✅ Considers edge cases proactively
- ✅ Strong testing strategy
- ✅ Discusses tradeoffs and alternatives
- ✅ Identifies potential improvements
- ✅ Production-ready code quality

---

## Additional Observations to Note

### Problem-Solving Process
- [ ] Systematic approach vs. trial and error
- [ ] Uses available tools (debugger, tests, documentation)
- [ ] Asks clarifying questions
- [ ] Thinks out loud / communicates well

### Technical Skills
- [ ] Comfortable with C++ syntax
- [ ] Understands testing frameworks (Catch2)
- [ ] Can navigate codebase efficiently
- [ ] Familiar with build systems (CMake/Just)

### Code Quality Awareness
- [ ] Notices the misleading comment
- [ ] Considers edge cases
- [ ] Thinks about maintainability
- [ ] Suggests improvements

---

## Interview Notes Template

**Candidate Name:** ___________________________  
**Date:** ___________________________  
**Position Level:** Junior / Mid / Senior

### Task Completion

| Task | Completed? | Time Taken | Quality |
|------|-----------|------------|---------|
| Task 1: Fix bug | ☐ Yes ☐ No | _____ min | ☐ Excellent ☐ Good ☐ Poor |
| Task 2: Add muting | ☐ Yes ☐ No | _____ min | ☐ Excellent ☐ Good ☐ Poor |
| Task 3: Delayed unmute | ☐ Yes ☐ No ☐ Partial | _____ min | ☐ Excellent ☐ Good ☐ Poor |
| Bonus improvements | ☐ Yes ☐ No | _____ min | ☐ Excellent ☐ Good ☐ Poor |

**Total Time:** _____ min

### Hints Used
- Task 1 hints: _____
- Task 2 hints: _____
- Task 3 hints: _____

### Task 1: Fix the Bug
- [ ] Found bug independently
- [ ] Fixed comparison operator (`<=` to `<`)
- [ ] Fixed misleading comment
- [ ] Verified fix with tests
- [ ] Understood why bug occurred

**Notes:**


### Task 2: Implement Muting
- [ ] Added mute/unmute correctly
- [ ] Placed in right location (`applyFilterState`)
- [ ] Understood when muting occurs
- [ ] Tests pass

**Notes:**


### Task 3: Delayed Unmute Design
- [ ] Recognized need for external time management
- [ ] Proposed clean API design
- [ ] Considered multiple approaches
- [ ] Extensible solution (not hardcoded)
- [ ] Added appropriate tests
- [ ] Discussed tradeoffs

**Design Approach Used:**
☐ Callback-based ☐ Deferred unmute ☐ Time-based ☐ Other: ___________

**Notes:**


### Observations

**Strengths:**




**Areas for Improvement:**




**Notable Moments:**




### Technical Skills Assessment
- [ ] Comfortable with C++ syntax
- [ ] Understands testing frameworks
- [ ] Can navigate codebase efficiently
- [ ] Uses debugger effectively
- [ ] Writes clean, maintainable code
- [ ] Good API design sense
- [ ] Considers edge cases
- [ ] Thinks about testability

### Communication & Process
- [ ] Reads documentation thoroughly
- [ ] Systematic problem-solving approach
- [ ] Asks clarifying questions
- [ ] Explains reasoning clearly
- [ ] Open to discussion and feedback

### Final Rating

**Task 1:** ⭐ Excellent / ✅ Good / ⚠️ Acceptable / ❌ Poor  
**Task 2:** ⭐ Excellent / ✅ Good / ⚠️ Acceptable / ❌ Poor  
**Task 3:** ⭐ Excellent / ✅ Good / ⚠️ Acceptable / ❌ Poor

**Overall:** ⭐ Strong Pass / ✅ Pass / ⚠️ Borderline / ❌ No Pass

**Recommendation:** ☐ Next Stage ☐ Maybe ☐ No

