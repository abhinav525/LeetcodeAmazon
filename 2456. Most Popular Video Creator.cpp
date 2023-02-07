//this solution giving time limit exceed
class Solution {
public:
    vector<vector<string>> mostPopularCreator(vector<string>& c, vector<string>& id, vector<int>& v) {
        unordered_map<string,long long>maxviews;
        unordered_map<string,string>ID;
        unordered_map<string,int>high;

        int n =c.size();
        for(int i=0;i<n;i++){
            maxviews[c[i]]+=v[i];
            //total num of views by any creator
            if(ID.find(c[i])==ID.end()){
                //if id of creator is not there in the databas then we will enter the id of creator and match its id with his views
                ID[c[i]]=id[i];
                high[c[i]]=v[i];


            }
            else{//if id is already there in database then check the high of the id if same then fill acc to lexiographically or if greater then it then update the views
                if(high[id[i]]==v[i])
                    ID[c[i]]=min(ID[c[i]],id[i]);
                else if(v[i]>high[id[i]]){
                    ID[c[i]]=id[i];
                    high[c[i]]=v[i];
                }
            }
        }
        priority_queue<pair<int,string>>pq;
        for(auto x: maxviews)//check max view channels
            pq.push({x.second,x.first});//1-view than creator name
        vector<vector<string>>ans;
        int popular=pq.top().first;
        while(!pq.empty() && pq.top().first==popular){
            vector<string>v;
            auto s=pq.top().second;
            pq.top();
            v.push_back(s);
            v.push_back(ID[s]);
            ans.push_back(v);
        }
        return ans;
        
        
    }
};

//another one
class Solution {
public:
    vector<vector<string>> mostPopularCreator(vector<string>& c, vector<string>& id, vector<int>& v) {
        unordered_map<string,long long>maxviews;
        unordered_map<string,pair<int,string>>video;
        

        int n =c.size();
        for(int i=0;i<n;i++){
            maxviews[c[i]]+=v[i];
            //total num of views by any creator
            if(video.count(c[i])==0) video[c[i]]={v[i],id[i]};
            else{
                int maxViews=video[c[i]].first;
                string max_play_video=video[c[i]].second;
                if(maxViews<v[i]){
                    video[c[i]]={v[i],id[i]};
                }
                else if(maxViews==v[i]){
                    video[c[i]]={v[i],min(id[i],max_play_video)};
                }
            }
        }
        long long max_pop=-1;
        for(auto i: maxviews){
            max_pop=max(max_pop,i.second);
        }
        vector<vector<string>>ans;
        for(auto i:maxviews){
            if(i.second==max_pop){
                ans.push_back({i.first,video[i.first].second});
            }
        }
        return ans;
    }
};
