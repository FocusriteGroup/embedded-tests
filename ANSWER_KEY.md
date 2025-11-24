# Interview Test - Answer Key

## The Bug

The bug is in `src/FilterManager.cpp` on line 16:

```cpp
bool shouldEnableFilter = (m_sampleRate <= 192000);
```

The condition uses `<=` (less than or equal) when it should use `<` (less than).

## The Fix

Change line 16 to:

```cpp
bool shouldEnableFilter = (m_sampleRate < 192000);
```

## Why This is the Bug

According to the specification:
- The filter should only be active at sample rates **below 192kHz**
- At 192kHz and above, the filter should be disabled

The current code enables the filter when `sampleRate <= 192000`, which means:
- ✅ 44.1kHz - filter enabled (correct)
- ✅ 48kHz - filter enabled (correct)
- ✅ 96kHz - filter enabled (correct)
- ❌ 192kHz - filter enabled (INCORRECT - should be disabled)
- ✅ 384kHz - filter disabled (correct)

With the fix (`sampleRate < 192000`), the behavior becomes:
- ✅ 192kHz - filter disabled (correct)

## Expected Candidate Approach

A good candidate should:

1. **Read the README** - Understand the problem context
2. **Run the tests** - Use `just test` to see the failures
3. **Analyze the failing test** - Look at the test expectations
4. **Locate the bug** - Find the comparison operator in FilterManager.cpp
5. **Make the fix** - Change `<=` to `<`
6. **Verify the fix** - Run tests again to confirm all pass

## Discussion Points

Use these to probe deeper:

### Code Quality
- "Are there any other potential issues with this code?"
- "How would you handle different edge cases (e.g., 0 Hz sample rate)?"
- "What happens if the hardware operations fail?"

### Testing
- "Are there any missing test cases?"
- "How would you test this with real hardware?"
- "What about thread safety?"

### Design
- "Why do we mute during transitions?"
- "What's the purpose of the interface abstraction?"
- "How would you extend this to support multiple filters?"

### Performance
- "Are there any performance concerns with this approach?"
- "What if setSampleRate is called very frequently?"

## Time Expectations

- Junior: 15-30 minutes
- Mid-level: 10-20 minutes
- Senior: 5-15 minutes

## Red Flags

- Can't run the tests
- Doesn't read the failing test output
- Makes random changes without understanding
- Doesn't verify the fix works
- Can't explain why the bug occurred

## Green Flags

- Systematically works through the problem
- Reads and understands test output
- Explains their reasoning
- Verifies the fix
- Suggests improvements or additional test cases
