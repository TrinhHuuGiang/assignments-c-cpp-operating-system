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
    
print(psutil.Process().environ())