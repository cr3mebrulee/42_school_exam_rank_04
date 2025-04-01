## THE SANDBOX TASK PURPOSE

This task is about creating a sandbox environment to run functions in a controlled way and determining whether the function is "nice" or "bad." The idea is to isolate the function execution so that if it misbehaves (e.g., crashes, times out, or exits with an error), it does not affect the overall system.

### WHAT SANDBOX IS

In the computer field, sandboxing is a security mechanism that isolates running programs, such as untrusted processes or code, to restrict their access permissions. The virtual environment contains some virtual hardware and software resources, such as file systems, networks, and operating systems, to run applications or processes. A sandboxed program can access only the limited number of resources inside the sandbox, without affecting the external application, system, or platform. This prevents the program from permanently changing other programs or data in the computer. In the cybersecurity field, sandboxing isolates malicious files to identify unknown attacks.

Three technologies are involved in sandboxing: virtualization, access control, and anti-evasion.

Different Types of Sandboxing

There are multiple types of sandboxing, depending on the scope and level of isolation:

- Application sandboxing (isolating entire applications from the OS and other apps);
- Process sandboxing (running a single process in a restricted environment);
- Virtualization-based sandboxing	(using a virtual machine to isolate software);
- Malware analysis sandboxing	(running malware in a controlled environment to study its behavior);
- Container sandboxing	(isolating applications using OS-level virtualization).

The assignment of 42's sanbox.c is about process sandboxing. Instead of isolating an entire application, we are isolating a single function (process) inside a controlled environment.

What our sandbox does:

- Runs an unknown function (f()) inside a separate process.
- Monitors if the function crashes, times out, or exits incorrectly.
- Prevents bad functions from affecting the main program.
- Ensures that no zombie processes remain after execution.

This is similar to application sandboxing, but at a smaller scale (process level).

### RESRTRICTED ENVIRONMENT IN SANDOX

Restricted environment means limiting what a process (or function) can do to prevent it from causing harm to the system. This includes restricting its access to system resources, execution time, and interactions with other processes.

A restricted environment imposes rules and limitations on a process. These restrictions prevent the process from:
✅ Crashing the system (e.g., through segmentation faults).
✅ Accessing unauthorized files or memory.
✅ Making dangerous system calls (e.g., deleting files, modifying kernel memory).
✅ Running indefinitely (enforcing a timeout).
✅ Becoming a zombie process (proper cleanup after execution).

### HOW IS A PROCESS RESTRICTED

The function int sandbox() will isolate process and run the untrusted function inside a separate process (child) so it cannot affect the main program. Main program will monitor the run time of the untrusted function and kill the process if it runs too long. Main program will detect crashes if they happen and handle signals (e.g., segmentation faults, illegal instructions). Finally, main program will monitore the exit status of the untrusted function and prevent zombie processes.

## PLAN TO IMPEMENT A 42'S SANDBOX

🔹 Step 1: Process Isolation
    The function f() is executed in a child process (fork()), so if it crashes, it doesn’t affect the parent.

🔹 Step 2: Timeout Mechanism
    If the function runs for too long, alarm(timeout) ensures it is killed after timeout seconds.

🔹 Step 3: Signal Handling (Catching Crashes)
    If f() causes a segfault (SIGSEGV), abort (SIGABRT), or any other signal, the program will detect it using sigaction().

🔹 Step 4: Monitoring Exit Status
    waitpid() helps determine why the function terminated:
        Exited normally? (Nice function ✅)
        Exited with an error code? (Bad function ❌)
        Crashed due to a signal? (Bad function ❌)

🔹 Step 5: Preventing Zombie Processes
    Ensures that no orphaned child processes remain by correctly using waitpid().

## SIGNALS HANDLING

When a process receives a signal, it is stored in the process's pending signal set inside the kernel until it is handled or ignored. The operating system manages signals using a combination of signal masks, pending signals, and process states.
1. Pending Signal Set (sigpending)

When a signal is sent to a process (via kill(), alarm(), or another method), it is added to the process's pending signal set. This is a bitmask stored in the process’s kernel structure. Each signal has a specific bit in this set. If a signal is blocked, it stays in the pending set until unblocked. If a signal is not blocked, the process handles it immediately.

2. Where Exactly is the Signal Stored?
Inside the Kernel Process Table

Each process in the system has a process descriptor (task_struct in Linux).
This structure contains:

    A pending signal queue (struct sigpending)

    A blocked signal mask (sigset_t blocked)

    The signal handler table (struct sighand_struct)

Kernel Signal Storage Example (Linux)

struct task_struct {
    sigset_t blocked;        // Mask of blocked signals
    struct sigpending pending;  // Signals that are pending
    struct sighand_struct *sighand;  // Signal handlers
};

💡 Key Takeaway:

    Pending signals are stored in pending.

    Blocked signals stay in pending until they are unblocked.

    Handled signals invoke a function and are then removed.

3. How the Kernel Processes a Signal

    Signal Sent:

        A signal (e.g., SIGALRM) is sent via kill(), alarm(), etc.

        The kernel adds it to the pending signal set in task_struct.

    Check Blocked Signals:

        If the signal is blocked (e.g., with sigprocmask()), it stays in pending.

        If it is not blocked, the process handles it immediately.

    Signal is Delivered:

        If a handler exists (sigaction() was set), it executes the function.

        If no handler exists, the default action occurs (terminate, ignore, etc.).

    Signal is Removed from Pending List:

        Once handled, the signal disappears from pending.

        If it was blocked, it stays in pending until unblocked.