//
// Created by shen on 2019/3/25.
//

#ifndef CODECRAFT_2019_CROSS_H
#define CODECRAFT_2019_CROSS_H

#include "road.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
#define NO_FIND ("NO_FIND")

struct order_info {
    int car_id;
    string road_name;
    int next_road_id;
    string next_road_name;
    string direction;
    bool priority;

    order_info() {
        car_id = -1;
        road_name = "";
        next_road_id = -1;
        next_road_name = "";
        direction = "";
        priority = false;
    }

    order_info(int carid, string r_name, int n_r_id, string n_r_name, string dir, bool prior) {
        car_id = carid;
        road_name = std::move(r_name);
        next_road_id = n_r_id;
        next_road_name = std::move(n_r_name);
        direction = std::move(dir);
        priority = prior;
    }
};


class Cross {
public:
    int crossID;        // 路口编号
    vector<int> roads;  // 道路分布
    vector<int> roads_prior_id; // 道路调度优先级 id表示
    vector<string> roads_prior_name;    //  道路调度优先级 name表示
    bool nothing2do;    // 时间片内路口调度结束
    int call_times;     // 时间片内调用处次数，表达该路口拥挤程度

    // 默认构造函数
    Cross();

    // 构造函数
    Cross(int cross_id, int road1, int road2, int road3, int road4, unordered_map<string, Road> &road_dict);

    // 路口调度道路的优先级，按照id升序
    vector<int> get_road_priors();

    // 根据道路ID和路口名称找道路名称
    string find_road_name_to_cross(unordered_map<string, Road> &road_dict, int road_id);

    // 重置路口完成标记
    void reset_end_flag();

    // 查询路口是否完成
    bool if_cross_ended();

    // 判断出路口转向
    string get_direction(int road_id, int next_road_id);

    // 判断有无直行进入目标车道的车辆发生冲突
    bool has_straight_to_conflict(unordered_map<int, order_info> &roads_map, int target_road_id, bool priority_car);

    // 判断有无直行或左转进入目标车道的车辆发生冲突
    bool has_straight_left_to_conflict(unordered_map<int, order_info> &roads_map, int target_road_id, bool priority_car);

    // 获取道路的出路口第一优先级车辆
    bool get_road_first_order_info(string road_name, unordered_map<string, Road> &road_dict,
                                   unordered_map<int, Car> &car_dict, int &road_id, order_info &first_order);

    // 获取第一优先级车辆信息
    unordered_map<int, order_info>
    get_first_order_info(unordered_map<string, Road> &road_dict, unordered_map<int, Car> &car_dict);

    // 跨路口移动车辆
    void move_car_across(Car &car_obj, Road &this_road, Road &next_road, unordered_map<int, Car> &car_dict);

    // 调度路口
    void update_cross(unordered_map<string, Road> &road_dict, unordered_map<int, Car> &car_dict, int loops_every_cross,
                      int time, Graph &graph);

    // 在路口调度时上路
    bool try_on_road_across(Car &car_obj, Road &next_road, unordered_map<int, Car> &car_dict);

    // 调度路口
    void process_cross(unordered_map<int, order_info> &next_roads, unordered_map<string, Road> &road_dict,
                       unordered_map<int, Car> &car_dict, int time, Graph &graph);

    // 有无优先车辆到目标道路
    bool has_prior_car_conflict(unordered_map<int, order_info> &roads_map, int target_road_id);
};

#endif //CODECRAFT_2019_CROSS_H
