//
//  KNPaginator.m
//  Neo
//
//  Created by Neo on 4/26/14.
//  Copyright (c) 2014 Neo. All rights reserved.
//

#import "KNPaginator.h"

@implementation KNPaginator


- (id)init{
    
    self = [super init];
    
    if( self ){
    
        self.dataArray = [[NSMutableArray alloc] init];
        
    }
    
    return self;
}

- (NSUInteger)count{

    return [self.dataArray count];

}

- (id)lastObject{
    
    return [self.dataArray lastObject];
    
}

- (id)firstObject{
    
    return [self.dataArray firstObject];
    
}

- (id)objectAtIndex:(NSUInteger)index{
    
    return [self.dataArray objectAtIndex:index];
    
}

- (void)fetchNew{
    

    [self.datasource fetchNewDataForPaginator:self withComplete:^(NSArray *dataArray) {
        
        if( [dataArray count] != 0 ){

            [self.dataArray insertObjects:dataArray atIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, [dataArray count])]];
            
            [self.delegate paginator:self didPreppendDataWithNumberOfData:[dataArray count]];
            
        }else{
            
            [self.delegate paginatorDidFetchTheLastObject:self];
            
        }
        
    } fail:^(NSError *error) {
        
        
        
    }];
    
}

- (void)nextPage{

    [self.datasource fetchDataForPaginator:self withComplete:^(NSArray *dataArray) {

        NSInteger orgNumber = [self count];

        if( [dataArray count] != 0 ){
            
            [self.dataArray addObjectsFromArray:dataArray];
            
            
            if( [self.datasource respondsToSelector:@selector(numberOfItemsPerFetch)]){
                
                NSInteger numberOfItem = [self.datasource numberOfItemsPerFetch];

                if( [dataArray count] < numberOfItem ){
                    self.isFinishedLoadedLastObject = YES;
                }
                
                [self.delegate paginator:self didAppendDataToIndex:orgNumber withNumberOfData:[dataArray count]];
                
                if( [dataArray count] < numberOfItem ){

                    [self.delegate paginatorDidFetchTheLastObject:self];
                }
                
                
            }else{
                
                [self.delegate paginator:self didAppendDataToIndex:orgNumber withNumberOfData:[dataArray count]];
            
            }
            
        }else{
            
            self.isFinishedLoadedLastObject = YES;
            
            [self.delegate paginator:self didAppendDataToIndex:orgNumber withNumberOfData:[dataArray count]];

            [self.delegate paginatorDidFetchTheLastObject:self];

            
        }
        
    } fail:^(NSError *error) {

    }];
    
}


- (void)reloadData{
    
    [self clearData];
    
    self.dataArray = [NSMutableArray arrayWithArray:self.tmpDataArray];
    
    self.tmpDataArray = nil;

}


- (void)clearData{
    
    self.dataArray = [[NSMutableArray alloc] init];
    self.isFinishedLoadedLastObject = NO;
    
    
}


@end
