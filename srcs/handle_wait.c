/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:39:15 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/16 10:45:02 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

// Check if the child process exited normally
bool wifexited(int status) {
    return (status & 0x7F) == 0; // If the lower 7 bits are zero, the process exited normally
}

// Get the exit status of the child process
int wexitstatus(int status) {
    if (wifexited(status)) {
        return (status >> 8) & 0xFF; // The exit status is stored in the upper byte
    }
    return -1; // Indicate invalid exit status
}

// Check if the child process was killed by a signal
bool wifsignaled(int status) {
    return (status & 0x7F) != 0 && (status & 0x7F) != 0x7F; // Lower 7 bits are non-zero and not 0x7F
}

// Get the signal number that caused the process to terminate
int wtermsig(int status) {
    if (wifsignaled(status)) {
        return status & 0x7F; // Signal number is stored in the lower 7 bits
    }
    return -1; // Indicate invalid signal number
}

// Check if the child process produced a core dump
bool wcoredump(int status) {
    return (status & 0x80) != 0; // Core dump flag is the 8th bit
}

// Check if the child process was stopped by a signal
bool wifstopped(int status) {
    return (status & 0xFF) == 0x7F; // If lower 8 bits are 0x7F, the process was stopped
}

// Get the signal number that stopped the process
int wstopsig(int status) {
    if (wifstopped(status)) {
        return (status >> 8) & 0xFF; // The stop signal is stored in the upper byte
    }
    return -1; // Indicate invalid stop signal
}

// Check if the child process was resumed by SIGCONT
bool wifcontinued(int status) {
    return status == 0xFFFF; // Specific value indicating SIGCONT resume
}

