# Baremetal Hardware Security Module
Cifradopro is a baremetal Hardware Security Module based on the STM32L4S5ZI microcontroller. It is capable of generating Random Keys in various sizes, Encrypting plaintext, and Decrypting ciphertext using the Advanced Encryption Standard. Additionally, it can create One-Time Pads of different lengths and generate a Hash of input data using the Secure Hashing Algorithm. 

[Under Development]: The module can store the generated cryptographic keys in an external memory device. As a safeguard against physical tampering, the device is designed to erase the contents of the external memory if the enclosure is breached.

For a detailed explanation and implementation guide, visit the article on my blog:
https://mbedsyst.blogspot.com/2024/03/hardware-security-module.html
