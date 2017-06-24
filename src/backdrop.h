#ifndef BACKDROP_H_
#define BACKDROP_H_

#include <string>
#include "graphics.h"

struct Backdrop {
    virtual void draw(Graphics& graphics) const = 0;
};

struct FixedBackdrop : public Backdrop {
    FixedBackdrop(const std::string& file_name, Graphics& graphics);
    void draw(Graphics& graphics) const;

private:
    Graphics::TextureID surface_id_;
};

#endif // BACKDROP_H_
