#include "runline.h"
RunLine::RunLine(QWidget *parent): QLabel(parent), m_shift(0), m_timerId(0) {

}

void RunLine::timerEvent(QTimerEvent *) {
  const int length = m_string.length();

  if(--m_shift <= 0)
    m_shift = length;

  setText(m_string.right(m_shift) + m_string.left(length - m_shift));
}

void RunLine::setSpeed(const int speed) {
  if (m_timerId)
    killTimer(m_timerId);
  m_timerId = 0;

  if(speed == 0){
      m_shift = 0;
      setText(m_string);
  }


  if (speed < 0)
    return;

  if (speed)
    m_timerId = startTimer(1000/speed);
}

void RunLine::setString(const QString string) {
  m_string = string;
  m_shift = 0;
  setText(m_string);
}
