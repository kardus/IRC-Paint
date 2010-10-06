#ifndef BLINE_COMMAND_H
#define BLINE_COMMAND_H

#include <utility>
#include <cstdlib>

#include <QUndoCommand>
#include <QColor>
#include <QImage>

class MainWidget;

/* Note to self:
 * Due to your own stupidity, this class
 * keeps a huge rectangle of the changed
 * area in memory.
 * This creates a problem when color
 * changing is added to the preferences.
 * Either fix that or just clear the undo
 * stack if the user changes preferences
 */

class BLine_Command : public QUndoCommand {
    int xstart, ystart, xend, yend;
    QColor col;
    QImage* img;
    MainWidget* widget;
    QImage changed;
public:
    BLine_Command(MainWidget* w, QImage* i, QColor c, int xs, int ys, int xe, int ye) : xstart(xs), ystart(ys), xend(xe), yend(ye), col(c), img(i), widget(w),
                                                                                        changed(i->copy(qMin(xs, xe), qMin(ys, ye), std::abs(xe-xs)+1, std::abs(ye-ys)+1)) { }
    void undo();
    void redo();
};

#endif // BLINE_COMMAND_H