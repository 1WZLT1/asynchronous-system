#include "rtio.h" 
#include <rthw.h>

void rtio_pool_init(rtio_node_t *rtio_node_head,\
										uint16_t    size,\
										rtio_t      *rtio
									 )
{
	rtio->free_list = NULL;
	for(int i=0;i<size;i++)
	{
		rtio_node_head[i].op    = 0;
		rtio_node_head[i].next  = NULL;
		rtio_node_head[i].state = RTIO_NODE_FREE;
		rtio_node_head[i].dev   = NULL;
	
		if(i == 0)
			rtio->free_list = &rtio_node_head[i];
		else 
			rtio_node_head[i-1].next = &rtio_node_head[i];
	}
	rtio->sq_head = rtio->sq_tail = \
  rtio->cq_head = rtio->cq_tail = NULL;
	rtio->Dev_busy_State = Dev_IDLE;
}

rtio_node_t *rtio_acquire(rtio_t *rtio)
{
	rt_base_t level;
	
	if(rtio == NULL)return NULL;
		
	level = rt_hw_interrupt_disable();
	if(rtio->free_list == NULL)
	{
		rt_hw_interrupt_enable(level);
		return NULL;
	}
	rtio_node_t *NodeCopy = rtio->free_list;
	rtio->free_list = NodeCopy->next;
	NodeCopy->next  = NULL;
	
	NodeCopy->state = RTIO_NODE_ALLOC;
	NodeCopy->dev   = NULL;
	NodeCopy->op    = 0;//操作类型
	
	rt_hw_interrupt_enable(level);
	return NodeCopy;
}

void rtio_submit_sq(rtio_t *rtio,rtio_node_t *node)
{
	rt_base_t level;
	if(rtio == NULL || node == NULL)return;
	level = rt_hw_interrupt_disable();
	
  node->next = RT_NULL;
  node->state = RTIO_NODE_IN_SQ;
	
	if (rtio->sq_tail == RT_NULL)
  {
    rtio->sq_head = node;
    rtio->sq_tail = node;
  }
  else
  {
    rtio->sq_tail->next = node;
    rtio->sq_tail       = node;
  }
	rt_hw_interrupt_enable(level);
}

rtio_node_t *rtio_sq_pop(rtio_t *rtio)
{
    rt_base_t level;
    rtio_node_t *node;

    if(rtio == RT_NULL)
        return RT_NULL;

    level = rt_hw_interrupt_disable();

    if(rtio->sq_head == RT_NULL)
    {
        rt_hw_interrupt_enable(level);
        return RT_NULL;
    }

    node = rtio->sq_head;
    rtio->sq_head = node->next;

    if(rtio->sq_head == RT_NULL)
    {
       rtio->sq_tail = RT_NULL;
    }

    node->next = RT_NULL;
    node->state = RTIO_NODE_EXEC;

    rt_hw_interrupt_enable(level);

    return node;
}

void rtio_release(rtio_t *rtio,rtio_node_t *node)
{
	rt_base_t level;
	if(rtio == NULL || node == NULL)return;
		
	level = rt_hw_interrupt_disable();
	
	node->state = RTIO_NODE_FREE;
	node->dev   = NULL;
	node->op    = 0;//操作类型
	
	rtio_node_t *Node_Copy = rtio->free_list;
	rtio->free_list        = node;
	rtio->free_list->next  = Node_Copy;
	
	rt_hw_interrupt_enable(level);
}
