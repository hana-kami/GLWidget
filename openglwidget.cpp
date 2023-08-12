#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent):  QGLWidget(parent)
{
    QGLFormat format;
    format.setVersion(2, 1);
    format.setProfile(QGLFormat::CoreProfile);
    setFormat(format);
    setWindowTitle(tr("MyOpenGL"));
    resize(640, 480);
    drawCube();
}
OpenGLWidget::~OpenGLWidget()
{
}
void OpenGLWidget::initializeGL()
{
    qDebug()<<glGetString(GL_VERSION)<<endl;
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(12.0);
}
void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/(float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glMultMatrixf(m_transform.constData());
    drawCube();
    glPopMatrix();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        rotate(dx, dy);
    } else if (event->buttons() & Qt::RightButton) {
        translate(dx, dy);
    }

    m_lastPos = event->pos();
    update();
}

void OpenGLWidget::drawCube()
{
    glBegin(GL_POINTS);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
}

void OpenGLWidget::rotate(int dx, int dy)
{
    m_rotation.setX(m_rotation.x() + dy);
    m_rotation.setY(m_rotation.y() + dx);

    QQuaternion xRot = QQuaternion::fromAxisAndAngle(1, 0, 0, m_rotation.x());
    QQuaternion yRot = QQuaternion::fromAxisAndAngle(0, 1, 0, m_rotation.y());
    m_transform.setToIdentity();
    m_transform.translate(m_translation);
    m_transform.rotate(xRot * yRot);
}

void OpenGLWidget::translate(int dx, int dy)
{
    m_translation.setX(m_translation.x() + dx * 0.01);
    m_translation.setY(m_translation.y() - dy * 0.01);

    m_transform.setToIdentity();
    m_transform.translate(m_translation);
    m_transform.rotate(QQuaternion::fromAxisAndAngle(1, 0, 0, m_rotation.x()));
    m_transform.rotate(QQuaternion::fromAxisAndAngle(0, 1, 0, m_rotation.y()));
}

