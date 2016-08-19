//
//  LivePlayerControlLayer.swift
//  TVSDKDemo
//
//  Created by wuguanyu on 16/8/19.
//  Copyright © 2016年 wuguanyu. All rights reserved.
//

import UIKit

class LivePlayerControlLayer: UIView {
    lazy var topBar: UIView = {
        let screenWidth = UIScreen.mainScreen().bounds.width
        let aView = UIView(frame: CGRect(x: 0, y: 0, width: screenWidth, height: 54))

        let gradient = CAGradientLayer()
        gradient.frame = aView.bounds
        gradient.colors = [UIColor(white: 0, alpha: 0.75).CGColor, UIColor.clearColor().CGColor]
        gradient.locations = [0.3, 1]
        aView.layer.insertSublayer(gradient, atIndex: 0)
        return aView
    }()
    
    lazy var bottomBar: UIView = {
        let screenSize = UIScreen.mainScreen().bounds
        let aView = UIView(frame: CGRect(x: 0, y: screenSize.height - 44, width: screenSize.width, height: 44))
        
        let gradient = CAGradientLayer()
        gradient.frame = aView.bounds
        gradient.colors = [UIColor.clearColor().CGColor, UIColor(white: 0, alpha: 0.75).CGColor]
        aView.layer.insertSublayer(gradient, atIndex: 0)
        
        return aView
    }()

    let screenSize = UIScreen.mainScreen().bounds
    
    let lockBtn: UIButton = {
        let aBtn = UIButton(type: .Custom)
        
        aBtn.setImage(UIImage(named: "6-1-1 全屏播放界面锁屏开启icon"), forState: .Selected)
        aBtn.setImage(UIImage(named: "6-1-1 全屏播放界面锁屏icon"), forState: .Normal)
        return aBtn
    }()
    
    let backBtn: UIButton = {
        let aBtn = UIButton(type: .Custom)
        
        aBtn.setImage(UIImage(named: "1-2 播放页全屏标题栏返回按钮"), forState: .Normal)
        return aBtn
    }()

    override init(frame: CGRect) {
        super.init(frame: frame)
        
        self.addSubview(topBar)
        self.addSubview(bottomBar)
        
        lockBtn.frame = CGRect(x: 10, y: screenSize.height / 2 - 22, width: 44, height: 44)
        lockBtn.addTarget(self, action: #selector(LivePlayerControlLayer.lockOrUnlock(_:)), forControlEvents: .TouchUpInside)
        lockBtn.alpha = 0.7
        self.addSubview(lockBtn)
        
        backBtn.frame = CGRect(x: 0, y: 10, width: 44, height: 44)
        topBar.addSubview(backBtn)
    }
    
    func lockOrUnlock(sender: UIButton) {
        if sender.selected {
            // locked
            sender.selected = false
            showControl()
        } else {
            // unlock
            sender.selected = true
            hideControl()
        }
    }
    
    func showControl() {
        topBar.hidden = false
        bottomBar.hidden = false
        lockBtn.hidden = false
    }
    
    func hideControl() {
        topBar.hidden = true
        bottomBar.hidden = true
        lockBtn.hidden = true
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
