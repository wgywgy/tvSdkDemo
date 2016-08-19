//
//  LivePlayerViewController.swift
//  TVSDKDemo
//
//  Created by wuguanyu on 16/8/19.
//  Copyright © 2016年 wuguanyu. All rights reserved.
//

import UIKit

class LivePlayerViewController: VideoPlayerController {
    let screenSize = UIScreen.mainScreen().bounds

    override func viewDidLoad() {
        super.viewDidLoad()

        NSNotificationCenter.defaultCenter().addObserver(self, selector: #selector(statusChanged(_:)), name: PlayerStatusChangedNotification, object: self)
        let screenWidth = screenSize.width
        
        let playerLayer = LivePlayerControlLayer(frame: CGRect(x: 0, y: 0, width: screenWidth, height: screenSize.height))
        self.view.addSubview(playerLayer)
    }

    func statusChanged(notify: NSNotification) {
        guard notify.object as? LivePlayerViewController == self else { return }
   
        guard let userInfo = notify.userInfo else { return }
        
        print("userInfo: \(userInfo)")
        
        guard let status = userInfo["status"]?.intValue else { return }
        print("status: \(status)")
        switch ePlayStatus(rawValue: UInt32(status)) {
        case E_PLAY_STATUS_OPENED:
            dispatch_async(dispatch_get_main_queue(), {
                self.play()
            })
        case E_PLAY_STATUS_OPEN_FAILED:
            print("play err")
            break
        default:
            break
        }
    }
    
    override func prefersStatusBarHidden() -> Bool {
        return false
    }
}
