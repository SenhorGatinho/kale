#include <algorithm>
#include "level.h"
#include "stuff.h"

#include "spriteeditwindow.h"
#include "ui_spriteeditwindow.h"

SpriteEditWindow::SpriteEditWindow(QWidget *parent, sprite_t *sprite) :
    QDialog(parent, Qt::CustomizeWindowHint
            | Qt::WindowTitleHint
            | Qt::WindowCloseButtonHint
            | Qt::MSWindowsFixedSizeDialogHint),
    ui(new Ui::SpriteEditWindow)
{
    ui->setupUi(this);

    this->sprite = sprite;

    for (StringMap::const_iterator i = spriteTypes.begin(); i != spriteTypes.end(); i++) {
            ui->comboBox->addItem(i->second, i->first);
    }

    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(setSpriteInfo(int)));

    ui->comboBox->setCurrentIndex(std::distance(spriteTypes.begin(),
                                                spriteTypes.find(sprite->type)));
    setSpriteInfo(ui->comboBox->currentIndex());

}

SpriteEditWindow::~SpriteEditWindow()
{
    delete ui;
}

void SpriteEditWindow::setSpriteInfo(int index) {
    // display any relevant info about the currently selected sprite
    uint spr = ui->comboBox->itemData(index).toUInt();
    QString text;

    switch (spr) {
    // TODO: some other handy notes if I can think of any

    // F7: warp star
    case 0xF7:
        text = "Warp stars must have an exit in the room to determine their destination. "
               "Placing more than one exit in the same room will have unpredictable results!\n\n"
               "Animation is determined by the current level and stage number. For stages which "
               "did not originally have a Warp Star, stage 1-2's animation will be used.";
        break;

    // F8: warp star 2
    case 0xF8:
        text = "This is an unused Warp Star variant with glitchy animation. "
               "Use type F7 instead.";
        break;

    // F9: cannon 1
    case 0xF9:
        text = "Launches Kirby into the next room.\n\n"
               "This cannon fires straight upward, except on stage 7-5, where it "
               "fires diagonally to the right.";
        break;

    // FA: cannon 2
    case 0xFA:
        text = "Launches Kirby into the next room.\n\n"
               "This cannon fires diagonally to the right.";
        break;

    // FE-FF: floor and ceiling switch
    case 0xFE:
    case 0xFF:
        text = "Switches must be placed on screen 0 or 1 of a 1-screen-wide room. "
               "Otherwise, the player will be returned to the incorrect location "
               "and the \"switch pressed\" animation may never finish, leading to "
               "glitchy behavior on the overworld.";
        break;
    }

    ui->label->setVisible(!text.isNull());
    ui->label->setText(text);
}

void SpriteEditWindow::accept() {
    this->sprite->type = ui->comboBox->itemData(ui->comboBox->currentIndex()).toUInt();

    QDialog::accept();
}
