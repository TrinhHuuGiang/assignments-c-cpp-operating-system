import psutil
# def on_terminate(proc):
#     print(f"Process {proc.pid} terminated with exit code {proc.returncode}")
# # Create a list of processes to wait for
# procs = [psutil.Process(pid) for pid in [1,2,3]]
# # Wait for the processes to terminate with a 10-second timeout
# gone, alive = psutil.wait_procs(procs, timeout=10, callback=on_terminate)
# print(f"Terminated processes: {gone}")
# print(f"Still running processes: {alive}")

try:
    p = psutil.Process(12345)  # Assuming process with PID 12345 doesn't exist
    print(p.name())
except psutil.NoSuchProcess as e:
    print(f"Process with PID 12345 not found: {e}")
    
# Get the current Python process
p = psutil.Process(psutil.Process().pid)

# Get the user IDs
uids = p.uids()

print(f"Real UID: {uids.real}")
print(f"Effective UID: {uids.effective}")
print(f"Saved UID: {uids.saved}")

terminal = p.terminal()

if terminal:
    print(f"Process is associated with terminal: {terminal}")
else:
    print("Process is not associated with a terminal.")
    

gids = p.gids()

print(f"Real GID: {gids.real}")
print(f"Effective GID: {gids.effective}")
print(f"Saved GID: {gids.saved}")

# Get the number of context switches
ctx_switches = p.num_ctx_switches()

print(f"Voluntary context switches: {ctx_switches.voluntary}")
print(f"Involuntary context switches: {ctx_switches.involuntary}")

num_fds = p.num_fds()

print(f"Số mô tả tệp của tiến trình: {num_fds}")
