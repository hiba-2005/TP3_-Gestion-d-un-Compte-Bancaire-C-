#include <iostream>
#include <iomanip>
#include <cstddef>
#include <algorithm>
#include <cstring>

class Buffer {
private:
    size_t size_;
    unsigned char* data_;

public:
    // --- Constructeur par défaut ---
    Buffer() : size_(0), data_(nullptr) {
        std::cout << "[Ctor défaut] Buffer vide (0 octet)\n";
    }

    // --- Constructeur paramétré ---
    explicit Buffer(size_t n) : size_(n), data_(nullptr) {
        if (n > 0) {
            data_ = new unsigned char[n];
            std::fill_n(data_, n, 0);
        }
        std::cout << "[Ctor param] Allocation d'un buffer de " << size_ << " octet(s)\n";
    }

    // Constructeur de copie
    Buffer(const Buffer& other) : size_(other.size_), data_(nullptr) {
        if (size_ > 0) {
            data_ = new unsigned char[size_];
            std::memcpy(data_, other.data_, size_);
        }
        std::cout << "[Ctor copie] Copie d'un buffer de " << size_ << " octet(s)\n";
    }

    // Opérateur d'affectation
    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this; // auto-affectation

        // Alloue une nouvelle zone avant de libérer l'ancienne (forte sécurité d'exception)
        unsigned char* newData = nullptr;
        if (other.size_ > 0) {
            newData = new unsigned char[other.size_];
            std::memcpy(newData, other.data_, other.size_);
        }

        // Libère l'ancienne
        delete[] data_;

        // Remplace par la nouvelle
        data_ = newData;
        size_ = other.size_;

        std::cout << "[Affectation] Maintenant " << size_ << " octet(s)\n";
        return *this;
    }

    // Destructeur
    ~Buffer() {
        std::cout << "[Destructeur] Destruction du buffer de " << size_ << " octet(s)\n";
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
    }

    // Méthodes publiques
    size_t getSize() const { return size_; }

    void fill(unsigned char value) {
        if (data_ && size_ > 0)
            std::fill_n(data_, size_, value);
    }

    void printHex() const {
        if (size_ == 0) {
            std::cout << "(vide)\n";
            return;
        }
        std::ios oldState(nullptr);
        oldState.copyfmt(std::cout);
        for (size_t i = 0; i < size_; ++i) {
            std::cout << std::uppercase << std::hex
                      << std::setw(2) << std::setfill('0')
                      << static_cast<int>(data_[i]);
            if (i + 1 < size_) std::cout << ' ';
        }
        std::cout << '\n';

        std::cout.copyfmt(oldState);
    }
};

int main() {
    std::cout << "=== Début du programme ===\n";

    // 1) Buffer par défaut
    Buffer b0;
    std::cout << "Buffer de " << b0.getSize() << " octet(s) : ";
    b0.printHex();

    // 2) Buffer de 8 octets, rempli avec 0xAA
    Buffer b8(8);
    b8.fill(0xAA);
    std::cout << "Buffer de " << b8.getSize() << " octet(s) : ";
    b8.printHex();

    // 3) Copie du second buffer (constructeur de copie)
    Buffer b8copy = b8;
    std::cout << "Copie : " << b8copy.getSize() << " octet(s) : ";
    b8copy.printHex();

    // 4) Démonstration de l'opérateur d'affectation (optionnel)
    b0 = b8copy;
    std::cout << "Après affectation, b0 (" << b0.getSize() << " octet(s)) : ";
    b0.printHex();

    std::cout << "=== Fin du programme ===\n";
    return 0;
}
