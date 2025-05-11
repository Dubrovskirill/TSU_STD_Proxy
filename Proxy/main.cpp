#include <iostream>
#include <string>

// Субъект (интерфейс)
class Image {
public:
    virtual void display() const = 0;
    virtual ~Image() = default;
};

// RealSubject (реальный объект)
class RealImage : public Image {
    std::string filename;
public:
    RealImage(const std::string& name) : filename(name) {
        std::cout << "Loading " << filename << std::endl;
    }
    void display() const override {
        std::cout << "Displaying " << filename << std::endl;
    }
};

// Proxy (заместитель)
class ImageProxy : public Image {
    std::string filename;
    mutable RealImage* realImage; // mutable для использования в const методе
public:
    ImageProxy(const std::string& name) : filename(name), realImage(nullptr) {}
    void display() const override {
        if (!realImage) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
    ~ImageProxy() { delete realImage; }
};

int main() {
    Image* proxy = new ImageProxy("test_10mb.jpg");
    // Первый вызов загрузит изображение
    proxy->display();
    // Второй вызов использует уже загруженное изображение
    proxy->display();
    delete proxy;
    return 0;
}
