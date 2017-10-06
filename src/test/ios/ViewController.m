//
//  ViewController.m
//  32423
//
//  Created by Nguyen Tuan on 10/6/17.
//  Copyright © 2017 Nguyen Tuan. All rights reserved.
//

#import "ViewController.h"
#include <asl.h>

@interface ViewController ()
@property (retain, nonatomic) IBOutlet UITextView *textView;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

-(void)display:(NSString *)text {
    self.textView.text = text;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
