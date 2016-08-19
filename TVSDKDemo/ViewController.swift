//
//  ViewController.swift
//  TVSDKDemo
//
//  Created by wuguanyu on 16/8/17.
//  Copyright © 2016年 wuguanyu. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var tableView: UITableView!
    var dataSource = []
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        tableView.delegate = self
        tableView.dataSource = self
    }

    @IBAction func getChannelList(sender: UIButton) {
        TVEngine.getChannellist { [weak self] (list, err) in
            guard let sself = self else { return }
            guard err == nil else {
                print("err: \(err)")
                return
            }
            
            sself.dataSource = list
            
            var channelId = [AnyObject]()
            for i in 0 ..< list.count {
                if let vid = sself.dataSource[i]["videoId"] {
                    channelId.append(vid!)
                }
            }
            TVEngine.getCurrentPlayingChannleWith(channelId, block: { (currentList, err) in
                print("currentList: \(currentList)")
                
            })
            dispatch_async(dispatch_get_main_queue(), {
                sself.tableView.reloadData()
            })
        }
    }
}

extension ViewController: UITableViewDelegate {
    func tableView(tableView: UITableView, heightForRowAtIndexPath indexPath: NSIndexPath) -> CGFloat {
        return 90
    }
}

extension ViewController: UITableViewDataSource {
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1
    }

    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let id = "cellId"
        let cell = tableView.dequeueReusableCellWithIdentifier(id) ?? UITableViewCell(style: .Default, reuseIdentifier: id)
        let videoName = dataSource[indexPath.row]["videoName"]
        cell.textLabel?.text = videoName as? String ?? ""
        
        return cell
    }
    
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return dataSource.count
    }
    
    func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        let vid = dataSource[indexPath.row]["videoId"] as? String ?? ""
        print("vid: \(vid)")
        let livePlayerVC = LivePlayerViewController()
        TVEngine.loadVideoWithID(vid, by: livePlayerVC, andType: "1", baseViewController: self)
    }
}
