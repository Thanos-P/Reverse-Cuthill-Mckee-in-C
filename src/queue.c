/*
 * @file   queue.c
 * @author athanasps <athanasps@ece.auth.gr>
 *         Thanos Paraskevas
 *
 */

#include "queue.h"

queue *queueInit (int queueSize)
{
  queue *q;

  q = (queue *)malloc (sizeof (queue));
  if (q == NULL) return (NULL);

  _queuesize = queueSize;
  q->buf = (node *)malloc (_queuesize * sizeof(node));

  q->empty = 1;
  q->full = 0;
  q->head = 0;
  q->tail = 0;

  return (q);
}

void queueDelete (queue *q)
{
  free (q->buf);
  free (q);
}

void queueAdd (queue *q, node val)
{
  q->buf[q->tail] = val;
  q->tail++;
  if (q->tail == _queuesize)
    q->tail = 0;
  if (q->tail == q->head)
    q->full = 1;
  q->empty = 0;

  return;
}

void queueDel (queue *q, node *val)
{
  *val = q->buf[q->head];

  q->head++;
  if (q->head == _queuesize)
    q->head = 0;
  if (q->head == q->tail)
    q->empty = 1;
  q->full = 0;

  return;
}
