/*
    This code is released under the terms of the MIT license.
    See COPYING.txt for details.
*/

#ifndef TILESETEDITWINDOW_H
#define TILESETEDITWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QAbstractButton>
#include <QPaintEvent>
#include <cstdint>
#include "level.h"
#include "tileset.h"
#include "hexspinbox.h"
#include "tilesetview.h"

namespace Ui {
class TilesetEditWindow;
}

// subclass of TilesetView that displays 8x8 tiles instead
class Tile8View : public TilesetView {
    Q_OBJECT

public:
    Tile8View(QWidget*, const QImage*);

public slots:
    void setPalette(int);

protected:
    void paintEvent(QPaintEvent*);
private:
    const QImage *gfxBanks;
    uint palette;
};

class TilesetEditWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit TilesetEditWindow(QWidget *parent);
    ~TilesetEditWindow();

    void startEdit(const leveldata_t *level);
    
public slots:
    void applySpeed(int);
    void animate();
    void setTileset(int);
    void setTile(int);
    void updateTile();
    void updateSubtract(int);
    void applyChange();
    void buttonClick(QAbstractButton*);

private:
    Ui::TilesetEditWindow *ui;

    HexSpinBox *tilesetBox, *tilePalBox, *subtractBox;
    HexSpinBox *tileBoxes[4];
    TilesetView *tileView;
    Tile8View *tile8View;

    QPixmap tilesetPixmap;
    QImage gfxBanks[4];
    uint tileset, currentTile;

    QTimer animTimer;
    uint animFrame;
    metatile_t tempTilesets[NUM_TILESETS][0x100];
    uint8_t    tempTileSubtract[NUM_TILESETS];

private slots:
    void accept();
    void refreshPixmap();

signals:
    void changed();
    void speedChanged(int);
};

#endif // TILESETEDITWINDOW_H
