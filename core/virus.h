#ifndef VIRUS_H
#define VIRUS_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QVector2D>
#include <QTimerEvent>

class Food;
class GameInterface;
class Ball;

class Virus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x NOTIFY x_change)
    Q_PROPERTY(int y READ y NOTIFY y_change)
    Q_PROPERTY(int radius READ radius NOTIFY radius_change)

public:
    explicit Virus(QRect *game_size, GameInterface *game_interface = nullptr, QObject *parent = nullptr);
    explicit Virus(Ball *ball_properties, GameInterface *game_interface = nullptr, QObject *parent = nullptr);
    static constexpr qreal _initial_mass = 22167;
    static constexpr qreal _radius = 84;
    // agario clone has the intial mass at 100-150, split at 180
    static constexpr qreal _split_mass = 34334;

    int x();
    int y();
    int radius();
    qreal mass();
    void add_mass(qreal mass);
    void handle_touch(Food *food);
    QPoint position();

signals:
    void x_changed();
    void y_changed();
    void radius_changed();

protected:
    void _connect_ball_property_signals();

private:
    Ball *_ball_properties;
    GameInterface *_game_interface;
};

#endif // VIRUS_H
