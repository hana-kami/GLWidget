#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <GL/glu.h>
class OpenGLWidget : public QGLWidget
{
public:
    OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();
protected:
    void initializeGL();
    void resizeGL(int w, int h);

    void paintGL();

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);


private:
    QVector3D m_rotation;
    QVector3D m_translation;
    QMatrix4x4 m_transform;
    QPoint m_lastPos;

    void drawCube();

    void rotate(int dx, int dy);

    void translate(int dx, int dy);

};

#endif // OPENGLWIDGET_H
