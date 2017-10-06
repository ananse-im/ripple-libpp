//
//  AppDelegate.m
//  32423
//
//  Created by Nguyen Tuan on 10/6/17.
//  Copyright © 2017 Nguyen Tuan. All rights reserved.
//

#import "AppDelegate.h"
#include "ripple-libpp_demo.h"
#import "ViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    dispatch_async(dispatch_get_main_queue(), ^{
        char* result = run();
        NSString *text = [[NSString alloc] initWithCString:result encoding:NSUTF8StringEncoding];
        ViewController *vc = (ViewController*)self.window.rootViewController;
        [vc display:text];
    });
    
    return YES;
}

- (void)redirectLog {
    
    NSArray<NSString*> *allPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, true);
    NSString* documentsDirectory = [allPaths firstObject];
    NSString *pathForLog = [documentsDirectory stringByAppendingPathComponent:@"/TestFile.txt"];

    [[NSFileManager defaultManager] removeItemAtPath:pathForLog error:nil];
    [[NSFileManager defaultManager] createFileAtPath:pathForLog contents:NULL attributes:NULL];
    freopen([pathForLog cStringUsingEncoding:NSUTF8StringEncoding], "a+", stderr);
    freopen([pathForLog cStringUsingEncoding:NSUTF8StringEncoding], "a+", stdin);
    freopen([pathForLog cStringUsingEncoding:NSUTF8StringEncoding], "a+", stdout);   
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
