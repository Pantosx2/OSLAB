# OS Lab — Exercise 2: lunix:TNG (NTUA 2023–24)

This README covers **Exercise 2**, which involved writing a **character device (chrdev)** driver for the **Linux** kernel. The full report is in [`ex2-lunix/ex2-lunix-report.pdf`](ex2-lunix/ex2-lunix-report.pdf).

## Goal
Implement and document the character-device side of **lunix:TNG** so that sensor readings are exposed correctly to user space.

## Key changes (in `lunix-chrdev.c`)
- **`lunix_chrdev_state_needs_refresh()`** — Check the state timestamp against the sensor’s last update to decide if a refresh is needed.
- **`lunix_chrdev_state_update()`** —
  - Uses: `sensor`, `new_data`, raw `data`, `looked_up_data`, `ret`, `digit`, `i`.
  - **Inside the spinlock:** verify refresh need, pull raw data from the sensor struct, update timestamp and `new_data`.
  - **Outside the lock:** convert raw data via lookup tables, format, and write into the state buffer.
- **`lunix_chrdev_open()`** — Get `minor` with `iminor`, derive sensor type (e.g., `minor/8`), `kzalloc` a per-file state, store in `file->private_data`, set type/number, init the semaphore.
- **`lunix_chrdev_read()`** — `down_interruptible` on the state semaphore; if at `*f_pos == 0` wait for fresh data (signal-aware); compute bytes to return, `copy_to_user`, release the semaphore, return count.
- **`lunix_chrdev_release()`** — Free the per-file state with `kfree`.
- **`lunix_chrdev_init()`** — Register device numbers with `register_chrdev_region` and add the device with `cdev_add`.
