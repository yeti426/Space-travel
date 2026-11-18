#include<stdio.h>
#include<string.h>
#include<limits.h>

#define MAXV 1005  //点
#define MAXE 4005  //边
#define NAME 10  //星球名字

//边结构体
typedef struct{
    int to;
    long long cap;
    int next;
}Edge;


Edge edge[MAXE];
int head[MAXV];
int edgecnt;

//names[id]=名字
char names[MAXV][NAME];
int namecnt;

//初始化图
void initGraph(void){
    edgecnt=0;
    namecnt=0;
    memset(head,-1,sizeof(head));
}

int getID(const char *s){
    for(int i=0;i<namecnt;i++){
        if(strcmp(names[i],s)==0) return i;
    }
    strcpy(names[namecnt],s);
    return namecnt++;
}

//加边
void addedge(int u,int v,long long c ){
    edge[edgecnt].to=v;
    edge[edgecnt].cap=c;
    edge[edgecnt].next=head[u];
    head[u]=edgecnt++;
    edge[edgecnt].to=u;
    edge[edgecnt].cap=0;
    edge[edgecnt].next=head[v];
    head[v]=edgecnt++;
    
}

//增广
int bfs(int s,int t,int V,int preV[],int preE[]) {
    int q[MAXV];
    int front=0, rear=0;

    for(int i=0;i<V;i++){
        preV[i]=-1;
        preE[i]=-1;
    }

    q[rear++]=s;
    preV[s]=s;

    while(front<rear){
        int u=q[front++];

        for(int i=head[u];i!=-1;i=edge[i].next) {
            int v=edge[i].to;
            if(preV[v]==-1&&edge[i].cap>0){
                preV[v]=u;
                preE[v]=i;
                q[rear++]=v;
                if(v==t)return 1;  // 找到汇点
            }
        }
    }
    return preV[t]!=-1;
}

//最大流
long long maxflow(int s,int t,int V){
    long long flow=0;
    int preV[MAXV],preE[MAXV];

    while(bfs(s,t,V,preV,preE)){
        //找路径上最小剩余容量
        long long aug=LLONG_MAX;
        for(int v=t;v!=s;v=preV[v]){
            int e=preE[v];
            if(edge[e].cap<aug) aug=edge[e].cap;
        }
        //增广：原边减，反向边加
        for(int v=t;v!=s;v=preV[v]){
            int e=preE[v];
            edge[e].cap-=aug;
            // 反向边下标：原边和反向边是成对加入的
            // 原边下标 e，反向边下标 e^1（因为成对加入，e 偶原边奇反向）
            edge[e^1].cap+=aug;
        }

        flow+=aug;
    }
    return flow;
}

int main(void){
    char start[NAME],end[NAME];
    int N;

    while(scanf("%s %s %d",start,end,&N)==3){
        if(N==0) break;

        initGraph();

        int S=getID(start);
        int T=getID(end);

        for(int i=0;i<N;i++){
            char u[NAME],v[NAME];
            long long c;
            scanf("%s %s %lld",u,v,&c);

            int a=getID(u);
            int b=getID(v);
            addEdge(a,b,c);
        }

        int V=namecnt;  // 当前点数
        printf("%lld\n",maxflow(S,T,V));
    }

    return 0;
}

#include<stdio.h>
#include<string.h>
#include<limits.h>

#define MAXV 1005  //点
#define MAXE 4005  //边
#define NAME 10  //星球名字

//边结构体
typedef struct{
    int to;
    long long cap;
    int next;
}Edge;


Edge edge[MAXE];
int head[MAXV];
int edgecnt;

//names[id]=名字
char names[MAXV][NAME];
int namecnt;

//初始化图
void initGraph(void){
    edgecnt=0;
    namecnt=0;
    memset(head,-1,sizeof(head));
}

int getID(const char *s){
    for(int i=0;i<namecnt;i++){
        if(strcmp(names[i],s)==0) return i;
    }
    strcpy(names[namecnt],s);
    return namecnt++;
}

//加边
void addedge(int u,int v,long long c ){
    edge[edgecnt].to=v;
    edge[edgecnt].cap=c;
    edge[edgecnt].next=head[u];
    head[u]=edgecnt++;
    edge[edgecnt].to=u;
    edge[edgecnt].cap=0;
    edge[edgecnt].next=head[v];
    head[v]=edgecnt++;
    
}

//增广
int bfs(int s,int t,int V,int preV[],int preE[]) {
    int q[MAXV];
    int front=0, rear=0;

    for(int i=0;i<V;i++){
        preV[i]=-1;
        preE[i]=-1;
    }

    q[rear++]=s;
    preV[s]=s;

    while(front<rear){
        int u=q[front++];

        for(int i=head[u];i!=-1;i=edge[i].next) {
            int v=edge[i].to;
            if(preV[v]==-1&&edge[i].cap>0){
                preV[v]=u;
                preE[v]=i;
                q[rear++]=v;
                if(v==t)return 1;  // 找到汇点
            }
        }
    }
    return preV[t]!=-1;
}

//最大流
long long maxflow(int s,int t,int V){
    long long flow=0;
    int preV[MAXV],preE[MAXV];

    while(bfs(s,t,V,preV,preE)){
        //找路径上最小剩余容量
        long long aug=LLONG_MAX;
        for(int v=t;v!=s;v=preV[v]){
            int e=preE[v];
            if(edge[e].cap<aug) aug=edge[e].cap;
        }
        //增广：原边减，反向边加
        for(int v=t;v!=s;v=preV[v]){
            int e=preE[v];
            edge[e].cap-=aug;
            // 反向边下标：原边和反向边是成对加入的
            // 原边下标 e，反向边下标 e^1（因为成对加入，e 偶原边奇反向）
            edge[e^1].cap+=aug;
        }

        flow+=aug;
    }
    return flow;
}

int main(void){
    char start[NAME],end[NAME];
    int N;

    while(scanf("%s %s %d",start,end,&N)==3){
        if(N==0) break;

        initGraph();

        int S=getID(start);
        int T=getID(end);

        for(int i=0;i<N;i++){
            char u[NAME],v[NAME];
            long long c;
            scanf("%s %s %lld",u,v,&c);

            int a=getID(u);
            int b=getID(v);
            addEdge(a,b,c);
        }

        int V=namecnt;  // 当前点数
        printf("%lld\n",maxflow(S,T,V));
    }

    return 0;
}