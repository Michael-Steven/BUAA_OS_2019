#include <env.h>
#include <pmap.h>
#include <printf.h>

/* Overview:
 *  Implement simple round-robin scheduling.
 *  Search through 'envs' for a runnable environment ,
 *  in circular fashion statrting after the previously running env,
 *  and switch to the first such environment found.
 *
 * Hints:
 *  The variable which is for counting should be defined as 'static'.
 */
/*
void sched_yield(void)
{
	static u_long count = 0;
	while (1) {
		count = (count + 1) % NENV;
		if (envs[count].env_status == ENV_RUNNABLE) {
			env_run(envs + count);
			return;
		}
	}
}
*/
/*
void sched_yield(void)
{
	static int count = 0;
	static int x = 0;
	static struct Env *cur;
	static int cur_env_pri;
	cur = LIST_FIRST(&env_sched_list[x]);
	//cur_env_pri = cur->env_pri;
	if (cur != NULL && count < cur->env_pri && cur->env_status == ENV_RUNNABLE) {
		count++;
	} else {
		do {
			if (cur != NULL){
				count = 1;
				LIST_REMOVE(cur, env_sched_link);
				LIST_INSERT_HEAD(&env_sched_list[1-x], cur, env_sched_link);
			}
			if (LIST_FIRST(&env_sched_list[x]) == NULL) {
				x = 1 - x;
			}
			cur = LIST_FIRST(&env_sched_list[x]);
			//cur_env_pri = cur->env_pri;
		} while (cur == NULL || cur->env_status != ENV_RUNNABLE);
	}
	if (cur != NULL){
		env_run(cur);
	}
}
*/

void sched_yield(void)
{
    int i;
    static int pos = 0;
    static int times = 0;
    static struct Env *e;
    if(--times <= 0){
    	do {
        	if(LIST_EMPTY(&env_sched_list[pos]))
        	{
            	pos = 1 - pos;
       		}
        	e = LIST_FIRST(&env_sched_list[pos]);
			if (e != NULL) {
        		LIST_REMOVE(e, env_sched_link);
        		LIST_INSERT_HEAD(&env_sched_list[1-pos], e, env_sched_link);
        		times = e->env_pri;
			}
    	}
		while(e == NULL || e->env_status != ENV_RUNNABLE);
	}
    env_run(e);
}

/*
void sched_yield(void)
{
	static int cur_time=0;
    static int x=0;
    static struct Env *cur = 0;
    while(cur_time==0 || (cur && cur->env_status != ENV_RUNNABLE)){
        if((LIST_FIRST(&env_sched_list[x]))==NULL){
            x = 1-x;
        }
        cur = LIST_FIRST(&env_sched_list[x]);
        cur_time = cur->env_pri;
        LIST_REMOVE(cur,env_sched_link);
        //LIST_INSERT_TAIL(&env_sched_list[1-x],cur,env_sched_link);
        LIST_INSERT_HEAD(&env_sched_list[1-x],cur,env_sched_link);

    }
    cur_time--;
    env_run(cur);	
}
*/
